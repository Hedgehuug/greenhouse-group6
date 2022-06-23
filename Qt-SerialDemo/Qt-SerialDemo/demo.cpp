/******************************************************************************
 * Project    : MIC2-V Serial demo
 * Copyright  : 2021 HAN University of Applied Sciences
 * Author     : Hugo Arends
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 ******************************************************************************
 */
#include "demo.h"
#include "ui_demo.h"

#include <QDebug>

Demo::Demo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Demo)
{
    ui->setupUi(this);

    htmlfile.setFileName("demo.html");
    if(!htmlfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file " << htmlfile.fileName();
        return;
    }

    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialRead()));
    connect(serial, SIGNAL(errorOccurred(QSerialPort::SerialPortError)),
            this, SLOT(serialError(QSerialPort::SerialPortError)));
}

Demo::~Demo()
{
    htmlfile.close();

    serial->close();
    delete serial;

    delete ui;
}

void Demo::exit()
{
    qApp->exit();
}

void Demo::rgbUpdate()
{
    bool red = this->ui->cbRed->isChecked();
    bool green = this->ui->cbGreen->isChecked();
    bool blue = this->ui->cbBlue->isChecked();

    qDebug() << "RGB updated: ["
             << red << ","
             << green << ","
             << blue << "]";

    if(serial->isOpen())
    {
        QByteArray data;
        data.append(red ? '1' : '0');
        data.append(green ? '1' : '0');
        data.append(blue ? '1' : '0');
        data.append('\n');

        serial->write(data);
        serial->flush();
    }
}

void Demo::serialConnect(void)
{
    // Set serial port parameters
    serial->setPortName(this->ui->lePortName->text());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Unable to connect to " << this->ui->lePortName->text();
        qDebug() << "Available COM ports are: ";

        QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

        if(serialPortInfos.length() == 0)
        {
            qDebug() << "None";
        }
        else
        {
            for(const QSerialPortInfo &serialPortInfo : serialPortInfos)
            {
                qDebug() << serialPortInfo.portName()
                         << " - "
                         << serialPortInfo.description();
            }
        }
    }
    else
    {
        qDebug() << "Successfully connected to " << this->ui->lePortName->text();

        serial->clear(QSerialPort::AllDirections);
        ui->pbConnect->setEnabled(false);
        ui->lePortName->setEnabled(false);

        this->rgbUpdate();
    }
}

void Demo::serialRead(void)
{
    if(!serial->isOpen())
    {
        return;
    }

    // Read all the bytes from the buffer into a local buffer
    rxbuffer.append(serial->readAll());

    // Synchronise on the \n character
    // The only supported string at this moment is a three digit
    // string that is terminated with a \n character. Here are some examples:
    //   "000\n"
    //   "432\n"
    //   "879\n"
    auto i = rxbuffer.indexOf('\n');
//    if(i != 3)
//    {
//        // If the input data is not alligned as expected, simply
//        // remove all data from the buffer and wait for new data
//        rxbuffer.clear();
//        return;
//    }

    // Replace the \n character with a \0 character.
    // This allows to read the first three chracaters as a string.
    rxbuffer[i] = '\0';

    // Show the received string
    ui->info->setText(rxbuffer.constData());

    // Clear the buffer
    rxbuffer.clear();

    // Create an HTML page and update the HTML file
    htmlfile.resize(0);
    QTextStream out(&htmlfile);
    out << "<!DOCTYPE html>";
    out << "<html>";
    out << "<head>";
    out << "  <title>MIC2-V</title>";
    out << "  <meta http-equiv=\"refresh\" content=\"2\">";
    out << "</head>";
    out << "<body>";
    out << "  <h1>MIC2-V Demo</h1>";
    out << "  <p>Number from the FRDM-KL25Z via the serial interface:</p>";
    out << ui->info->text();
    out << "</body>";
    out << "</html>";
}

void Demo::serialError(QSerialPort::SerialPortError error)
{
    if(error != QSerialPort::NoError)
    {
        qDebug() << "Serial error: " << error;
    }
}

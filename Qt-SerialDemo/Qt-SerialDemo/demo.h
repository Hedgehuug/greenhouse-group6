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
#ifndef DEMO_H
#define DEMO_H

#include <QMainWindow>

#include <QFile>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Demo; }
QT_END_NAMESPACE

class Demo : public QMainWindow
{
    Q_OBJECT

public:
    Demo(QWidget *parent = nullptr);
    ~Demo();

public slots:
    void rgbUpdate();
    void serialConnect();
    void exit();

    void serialRead(void);
    void serialError(QSerialPort::SerialPortError error);

private:
    Ui::Demo *ui;

    QFile htmlfile;

    QSerialPort *serial;
    QByteArray rxbuffer;
};
#endif // DEMO_H

#include "mainwindow.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    mainLayout = new QGridLayout();
    menu();
    setWindowTitle(tr("GreenHouse by Bazil Bozos"));
}

Dialog::~Dialog()
{
    serial->close();
    delete serial;
}

void Dialog :: menu()
{
    createLabel();
    createMenuButtons();

    formMenu = new QVBoxLayout;
    formMenu -> addWidget(label);
    formMenu -> addWidget(forButtons);

    forMenu = new QGroupBox;
    forMenu -> setLayout(formMenu);
    mainLayout -> addWidget(forMenu,0,0);
    setLayout(mainLayout);
}

void Dialog :: developer()
{       
    createDevInputs();
    createUserInputs();
    createBackButton();

    formDevLayout = new QVBoxLayout;
    formDevLayout -> addWidget(forDevInputs);
    formDevLayout -> addWidget(forUserInputs);
    formDevLayout -> addWidget(bButton);

    forDeveloper = new QGroupBox;
    forDeveloper -> setLayout(formDevLayout);
    mainLayout -> addWidget(forDeveloper,0,0);
    setLayout(mainLayout);
}

void Dialog :: user()
{   
    createUserInputs();
    createBackButton();

    formUserLayout = new QVBoxLayout;
    formUserLayout -> addWidget(forUserInputs);
    formUserLayout -> addWidget(bButton);

    forUser = new QGroupBox;
    forUser -> setLayout(formUserLayout);
    mainLayout -> addWidget(forUser,0,0);
    setLayout(mainLayout);
}

void Dialog :: createLabel()
{
    label = new QLabel (this);
    label->setAlignment(Qt::AlignCenter);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("GREENHOUSE PROTOTYPE APP");
    //label->setGeometry(QRect(QPoint(100,100),QSize(100,50)));
}


void Dialog :: createMenuButtons()
{
    QPushButton *menuButtons1 = new QPushButton ("Developer");
    QPushButton *menuButtons2 = new QPushButton ("User");
    QPushButton *menuButtons3 = new QPushButton ("Close");

    connect(menuButtons1, SIGNAL(clicked()), this, SLOT(pushDeveloper()));
    connect(menuButtons2, SIGNAL(clicked()), this, SLOT(pushUser()));
    connect(menuButtons3, SIGNAL(clicked()), this, SLOT(pushClose()));

    buttonLayout = new QHBoxLayout;
    buttonLayout -> addWidget(menuButtons1);
    buttonLayout -> addWidget(menuButtons2);
    buttonLayout -> addWidget(menuButtons3);

    forButtons = new QGroupBox;
    forButtons -> setLayout(buttonLayout);
}

void Dialog :: createDevInputs()
{   
    flagLabelHeater= new QLabel(tr("Heater"));
    flagLabelFan = new QLabel(tr("Fan"));
    flagLabelPump = new QLabel(tr("Pump"));
    flagLabelLight = new QLabel(tr("Light"));

    flagHeater = new QLabel();
    flagFan = new QLabel();
    flagPump = new QLabel();
    flagLight = new QLabel();

    labelDisplayTemp = new QLabel(tr("Temperature"));
    labelDisplayHumid = new QLabel(tr("Humidity"));
    labelDisplaySoilMoist = new QLabel(tr("Soil Moisture"));
    labelDisplayLightLevel = new QLabel(tr("Light Level"));

    displayTemp = new QLabel;
    displayTemp -> setText(QString("%1").arg(temp));
    displayHumid = new QLabel;
    displayHumid -> setText(QString("%1").arg(humid));
    displaySoilMoist = new QLabel;
    displaySoilMoist -> setText(QString("%1").arg(soilMoist));
    displayLightLevel = new QLabel;
    displayLightLevel -> setText(QString("%1").arg(lightLevel));

    flagHeater -> setText("Nan");
    flagFan -> setText("Nan");
    flagPump-> setText("Nan");
    flagLight -> setText("Nan");

    formDevInputs = new QFormLayout;
    formDevInputs -> addRow(flagLabelHeater, flagHeater);
    formDevInputs -> addRow(flagLabelFan, flagFan);
    formDevInputs -> addRow(flagLabelPump, flagPump);
    formDevInputs -> addRow(flagLabelLight, flagLight);
    formDevInputs -> addRow(labelDisplayTemp, displayTemp);
    formDevInputs -> addRow(labelDisplayHumid, displayHumid);
    formDevInputs -> addRow(labelDisplaySoilMoist, displaySoilMoist);
    formDevInputs -> addRow(labelDisplayLightLevel, displayLightLevel);

    forDevInputs = new QGroupBox;
    forDevInputs -> setLayout(formDevInputs);
}

void Dialog :: createUserInputs()
{
    serial = new QSerialPort();
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialRead()));
    connect(serial, SIGNAL(errorOccurred(QSerialPort::SerialPortError)),
            this, SLOT(serialError(QSerialPort::SerialPortError)));

    QLabel *labelInfo = new QLabel(tr("Info"));
    buttonc = new QPushButton(tr("PORT"));
    COM = new QLineEdit();
    info = new QLabel();

    connect(buttonc, SIGNAL(clicked()), this, SLOT(serialConnect()));

    QPushButton *buttonFanTriggerTemp = new QPushButton(tr("Fan trigger temperature"));
    QPushButton *buttonHeaterTriggerTemp = new QPushButton(tr("Heater trigger temperature"));
    QPushButton *buttonSoilMoistTrigger = new QPushButton(tr("Moisture %level trigger"));
    QPushButton *buttonLightLevelTrigger = new QPushButton(tr("Light %level trigger"));

    fanTriggerTemp = new QLineEdit;
    heaterTriggerTemp = new QLineEdit;
    soilMoistureTrigger = new QLineEdit;
    lightLevelTrigger = new QLineEdit;

    fanTriggerTemp -> setText(QString("%1").arg(fanTrigger));
    heaterTriggerTemp -> setText(QString("%1").arg(heaterTrigger));
    soilMoistureTrigger -> setText(QString("%1").arg(soilMoistTrigger));
    lightLevelTrigger -> setText(QString("%1").arg(lightLevel));

    connect(buttonFanTriggerTemp, SIGNAL(clicked()), this, SLOT(pushFanTrigger()));
    connect(buttonSoilMoistTrigger, SIGNAL(clicked()), this , SLOT(pushSoilMoistTrigger()));
    connect(buttonHeaterTriggerTemp, SIGNAL(clicked()), this, SLOT(pushHeaterTrigger()));
    connect(buttonLightLevelTrigger, SIGNAL(clicked()), this, SLOT(pushLightTrigger()));

    formUserInputs = new QFormLayout;

    formUserInputs -> addRow(buttonFanTriggerTemp, fanTriggerTemp);
    formUserInputs -> addRow(buttonHeaterTriggerTemp, heaterTriggerTemp);
    formUserInputs -> addRow(buttonLightLevelTrigger, lightLevelTrigger);
    formUserInputs -> addRow(buttonSoilMoistTrigger, soilMoistureTrigger);
    formUserInputs -> addRow(buttonc, COM);
    formUserInputs -> addRow(labelInfo, info);

    forUserInputs = new QGroupBox;
    forUserInputs -> setLayout(formUserInputs);
}

void Dialog :: createBackButton()
{
    bButton = new QPushButton(tr("back"));
    connect(bButton, SIGNAL(clicked()), this, SLOT(pushBack()));
}

void Dialog :: pushDeveloper()
{
    deleteWidget();
    developer();
}

void Dialog :: pushUser()
{
    deleteWidget();
    user();
}

void Dialog :: pushBack()
{
    deleteWidget();
    menu();
}

void Dialog :: deleteWidget()
{
    QLayoutItem *item = mainLayout -> itemAt(0);
    mainLayout -> removeItem(item);
    QWidget* widget = item->widget();
    if(widget)
    {
        delete widget;
    }
}

void Dialog :: checkBoolHeater(int a)
{

    if (a == 0)
    {
        flagHeater -> setText("Off");
    }else
    {
        flagHeater -> setText("On");
    }
}

void Dialog :: checkBoolFan(int b)
{

    if (b == 0)
    {
        flagFan -> setText("Off");
    }else
    {
        flagFan -> setText("On");
    }
}

void Dialog :: checkBoolPump(int c)
{
    if (c == 0)
    {
        flagPump -> setText("Off");
    }else
    {
        flagPump -> setText("On");
    }
}

void Dialog :: checkBoolLight(int d)
{
    if (d == 0)
    {
        flagLight -> setText("Off");
    }else
    {
        flagLight -> setText("On");
    }
}

void Dialog :: pushFanTrigger()
{
    bool check;
    fanTrigger = fanTriggerTemp->text();
    int tN = fanTrigger.toInt(&check);
    if(!check)
    {
        tN = 40;
        qDebug() << "Please enther a nummber";
    }
    if(tN > 40)
    {
        tN = 40;
        qDebug() << "Number is above 40, automatically set to 40";
    }
    if(tN < 0)
    {
        tN = 0;
        qDebug() << "Number is below 0, automatically set to 0";
    }
    fanTrigger = QString("%1").arg(tN);

    updateFanTrigger();

    if(serial->isOpen())
    {
        QByteArray data;
        data.append('t'); //"t"
        data.append(fanTrigger.toStdString());
        data.append("\n"); //"t...\n"

        serial->write(data);
        serial->flush();
    }
}

void Dialog :: pushHeaterTrigger()
{
    bool check;
    heaterTrigger = heaterTriggerTemp->text();
    int tN = heaterTrigger.toInt(&check);
    if(!check)
    {
        tN = 40;
        qDebug() << "Please enter a nummber";
    }
    if(tN > 40)
    {
        tN = 40;
        qDebug() << "Number is above 40, automatically set to 40";
    }
    if(tN < 0)
    {
        tN = 0;
        qDebug() << "Number is below 0, automatically set to 0";
    }
    heaterTrigger = QString("%1").arg(tN);

    updateHeaterTrigger();

    if(serial->isOpen())
    {
        QByteArray data;
        data.append('h'); //"h"
        data.append(heaterTrigger.toStdString());
        data.append("\n"); //"h...\n"

        serial->write(data);
        serial->flush();
    }
}

void Dialog :: pushSoilMoistTrigger()
{
    bool check;
    soilMoistTrigger = soilMoistureTrigger->text();
    int tN = soilMoistTrigger.toInt(&check);
    if(!check)
    {
        tN = 0;
        qDebug() << "Please enther a nummber";
    }
    if(tN > 100)
    {
        tN = 100;
        qDebug() << "Number is above 100, automatically set to 100";
    }
    if(tN < 0)
    {
        tN = 0;
        qDebug() << "Number is below 0, automatically set to 0";
    }
    soilMoistTrigger = QString("%1").arg(tN);

    updateSoilMoistureTrigger();

    if(serial->isOpen())
    {
        QByteArray data;
        data.append('s'); //"l"
        data.append(soilMoistTrigger.toStdString());
        data.append('\n'); //"l...\n"

        serial->write(data);
        serial->flush();
    }
}

void Dialog :: pushLightTrigger()
{
    bool check;
    lightTrigger = lightLevelTrigger->text();
    int tN = lightTrigger.toInt(&check);
    if(!check)
    {
        tN = 0;
        qDebug() << "Please enther a nummber";
    }
    if(tN > 100)
    {
        tN = 100;
        qDebug() << "Number is above 100, automatically set to 100";
    }
    if(tN < 0)
    {
        tN = 0;
        qDebug() << "Number is below 0, automatically set to 0";
    }
    lightTrigger = QString("%1").arg(tN);

    updateLightTrigger();

    if(serial->isOpen())
    {
        QByteArray data;
        data.append('l'); //"l"
        data.append(lightTrigger.toStdString());
        data.append('\n'); //"l...\n"

        serial->write(data);
        serial->flush();
    }
}

void Dialog :: updateActuators()
{
    checkBoolHeater(boolHeater);
    checkBoolFan(boolFan);
    checkBoolPump(boolPump);
    checkBoolLight(boolLight);

    qDebug() << "Actuators updated: ["
             << boolHeater << ","
             << boolFan << ","
             << boolPump << ","
             << boolLight << "]";
}

void Dialog :: updateTemperature()
{
    displayTemp -> setText(QString("%1").arg(temp));
    qDebug() << "Temperature: ["
             << displayTemp->text() << "]";
}

void Dialog :: updateHumidity()
{
    displayHumid -> setText(QString("%1").arg(humid));
    qDebug() << "Humidity updated: ["
             << displayHumid->text() << "]";
}

void Dialog :: updateSoilMoisture()
{
    displaySoilMoist -> setText(QString("%1").arg(soilMoist));
    qDebug() << "Soil Moisture updated: ["
             << displaySoilMoist->text() << "]";
}

void Dialog :: updateLight()
{
    displayLightLevel -> setText(QString("%1").arg(lightLevel));
    qDebug() << "Light Level updated: ["
             << displayLightLevel->text() << "]";
}

void Dialog :: updateFanTrigger()
{
    fanTriggerTemp -> setText(QString("%1").arg(fanTrigger));
    qDebug() << "Fan Trigger updated: ["
             << fanTriggerTemp->text() << "]";
}

void Dialog :: updateHeaterTrigger()
{
    heaterTriggerTemp -> setText(QString("%1").arg(heaterTrigger));
    qDebug() << "Heater Trigger updated: ["
             << heaterTriggerTemp->text() << "]";
}

void Dialog :: updateSoilMoistureTrigger()
{
    soilMoistureTrigger -> setText(QString("%1").arg(soilMoistTrigger));
    qDebug() << "Soil Moisture Trigger updated: ["
             << soilMoistureTrigger->text() << "]";
}

void Dialog :: updateLightTrigger()
{
    lightLevelTrigger -> setText(QString("%1").arg(lightTrigger));
    qDebug() << "Light Trigger updated: ["
             << lightLevelTrigger->text() << "]";
}

void Dialog :: serialConnect(void)
{
    // Set serial port parameters
    serial->setPortName(COM->text());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Unable to connect to " << COM->text();
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
        qDebug() << "Successfully connected to " << COM->text();

        serial->clear(QSerialPort::AllDirections);
        buttonc->setEnabled(false);
        COM->setEnabled(false);

        temp = QString("0");
        humid = QString("0");
        soilMoist = QString("0");
        lightLevel = QString("0");

        heaterTrigger = QString("22");
        fanTrigger = QString("29");
        soilMoistTrigger = QString("20");
        lightTrigger = QString("10");

        updateActuators();
        updateTemperature();
        updateHumidity();
        updateSoilMoisture();
        updateLight();
        updateFanTrigger();
        updateHeaterTrigger();
        updateSoilMoistureTrigger();
        updateLightTrigger();
    }
}

void Dialog :: serialRead(void)
{
    if(!serial->isOpen())
    {
        return;
    }

    rxbuffer.append(serial->readAll());
    qDebug() << rxbuffer;

    // Synchronise on the \n character
    // string that is terminated with a \n character. Here are some examples:
    auto i = rxbuffer.indexOf('\n');
    // Replace the \n character with a \0 character.
    rxbuffer[i] = '\0';

    char firstC = rxbuffer[0];

    switch(firstC)
    {
    case 'a':
        rxbuffer[i] = '\0';
        boolHeater = rxbuffer[1]-48;
        boolFan = rxbuffer[2]-48;
        boolPump = rxbuffer[3]-48;
        boolLight = rxbuffer[4]-48;
        updateActuators();
        break;

    case 't':
        rxbuffer[i] = '\0';
        temp = rxbuffer.constData()+1;
        updateTemperature();
        break;

    case 'h':
        rxbuffer[i] = '\0';
        humid = rxbuffer.constData()+1;;
        updateHumidity();
        break;

    case 's':
        rxbuffer[i] = '\0';
        soilMoist = rxbuffer.constData()+1;
        updateSoilMoisture();
        break;

    case 'l':
        rxbuffer[i] = '\0';
        lightLevel = rxbuffer.constData()+1;
        updateLight();
        break;

    case 'f':
        rxbuffer[i] = '\0';
        fanTrigger = rxbuffer.constData()+1;
        qDebug() << "Fan Trigger updated: ["
                 << fanTriggerTemp->text() << "]";
        break;

    case'e':
        rxbuffer[i] = '\0';
        heaterTrigger = rxbuffer.constData()+1;
        qDebug() << "Heater Trigger updated: ["
                 << heaterTriggerTemp->text() << "]";
        break;

    case 'i':
        rxbuffer[i] = '\0';
        lightTrigger = rxbuffer.constData()+1;
        qDebug() << "Light Trigger updated: ["
                 << lightLevelTrigger->text() << "]";
        break;
    case 'm':
        rxbuffer[i] = '\0';
        soilMoistTrigger = rxbuffer.constData()+1;
        qDebug() << "Soil Moist Trigger updated: ["
                 << soilMoistureTrigger->text() << "]";

    default:
        info -> setText(tr("Problem with identifying the text"));
        break;
    }
    // Show the received string
    info->setText(rxbuffer.constData());

    // Clear the buffer
    rxbuffer.clear();
}

void Dialog :: serialError(QSerialPort::SerialPortError error)
{
    if(error != QSerialPort::NoError)
    {
        qDebug() << "Serial error: " << error;
    }
}

void Dialog :: pushClose()
{
    this->close();
}


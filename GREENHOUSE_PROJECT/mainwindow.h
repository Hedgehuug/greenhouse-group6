#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QVBoxLayout>
#include <QDialog>
#include <QPushButton>
#include <QLayout>
#include <QSize>
#include <QGroupBox>
#include <QLineEdit>
#include <QLayoutItem>
#include <QFormLayout>
#include <QComboBox>
#include <QString>
#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QByteArray>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
     void menu();
     void developer();
     void user();

     void createLabel();
     void createMenuButtons();
     void createDevInputs();
     void createUserInputs();
     void createBackButton();

     void pushDeveloper();
     void pushUser();
     void pushClose();
     void pushBack();

     void pushFanTrigger();
     void pushHeaterTrigger();
     void pushLightTrigger();

     void deleteWidget();

     void checkBoolHeater(int a);
     void checkBoolFan(int b);
     void checkBoolPump(int c);
     void checkBoolLight(int d);

     void updateActuators();
     void updateTemperature();
     void updateHumidity();
     void updateSoilMoisture();
     void updateLight();
     void updateFanTrigger();
     void updateHeaterTrigger();
     void updateLightTrigger();

     void serialConnect();
     void serialRead(void);
     void serialError(QSerialPort::SerialPortError error);

private:     
    int boolHeater = 0;
    int boolFan = 0;
    int boolPump = 0;
    int boolLight = 0;

    QString temp = "Nan";
    QString humid = "Nan";
    QString soilMoist = "Nan";
    QString lightLevel = "Nan";

    QString fanTrigger = "Nan";
    QString heaterTrigger = "Nan";
    QString lightTrigger = "Nan";

    QString Sentence[8];

    QLabel *flagLabelHeater;
    QLabel *flagLabelFan;
    QLabel *flagLabelPump;
    QLabel *flagLabelLight;

    QLabel *labelDisplayTemp;
    QLabel *labelDisplayHumid;
    QLabel *labelDisplaySoilMoist;
    QLabel *labelDisplayLightLevel;

    QLabel *displayTemp;
    QLabel *displayHumid;
    QLabel *displaySoilMoist;
    QLabel *displayLightLevel;

    QPushButton *buttonc;
    QFile htmlfile;

    QLineEdit *fanTriggerTemp;
    QLineEdit *heaterTriggerTemp;
    QLineEdit *lightLevelTrigger;

    QLineEdit *COM;
    QLabel *info;
    QLabel *userMoist;

    QPushButton *bButton;
    QGroupBox *forButtons;
    QGroupBox *forDevInputs;
    QGroupBox *forUserInputs;
    QHBoxLayout *buttonLayout;
    QGroupBox *forMenu;
    QGroupBox *forDeveloper;
    QGroupBox *forUser;

    QVBoxLayout *formMenu;
    QVBoxLayout *formDevLayout;
    QFormLayout *formDevInputs;
    QVBoxLayout *formUserLayout;
    QFormLayout *formUserInputs;
    QGridLayout *mainLayout;
    QLabel *label;
    QLabel *Label1;   

    QLabel *flagHeater;
    QLabel *flagFan;
    QLabel *flagPump;
    QLabel *flagLight;

    QByteArray rxbuffer;
    QSerialPort *serial;
};
#endif // MAINWINDOW_H

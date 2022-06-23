/********************************************************************************
** Form generated from reading UI file 'demo.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMO_H
#define UI_DEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Demo
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pbConnect;
    QLineEdit *lePortName;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *cbRed;
    QCheckBox *cbGreen;
    QCheckBox *cbBlue;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *info;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Demo)
    {
        if (Demo->objectName().isEmpty())
            Demo->setObjectName(QString::fromUtf8("Demo"));
        Demo->resize(212, 362);
        centralwidget = new QWidget(Demo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pbConnect = new QPushButton(centralwidget);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));

        verticalLayout->addWidget(pbConnect);

        lePortName = new QLineEdit(centralwidget);
        lePortName->setObjectName(QString::fromUtf8("lePortName"));

        verticalLayout->addWidget(lePortName);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        cbRed = new QCheckBox(groupBox);
        cbRed->setObjectName(QString::fromUtf8("cbRed"));

        verticalLayout_2->addWidget(cbRed);

        cbGreen = new QCheckBox(groupBox);
        cbGreen->setObjectName(QString::fromUtf8("cbGreen"));

        verticalLayout_2->addWidget(cbGreen);

        cbBlue = new QCheckBox(groupBox);
        cbBlue->setObjectName(QString::fromUtf8("cbBlue"));

        verticalLayout_2->addWidget(cbBlue);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        info = new QLineEdit(groupBox_2);
        info->setObjectName(QString::fromUtf8("info"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(info->sizePolicy().hasHeightForWidth());
        info->setSizePolicy(sizePolicy);
        info->setReadOnly(true);

        verticalLayout_3->addWidget(info);


        verticalLayout->addWidget(groupBox_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        Demo->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Demo);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 212, 21));
        Demo->setMenuBar(menubar);
        statusbar = new QStatusBar(Demo);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Demo->setStatusBar(statusbar);

        retranslateUi(Demo);
        QObject::connect(cbRed, SIGNAL(clicked()), Demo, SLOT(rgbUpdate()));
        QObject::connect(cbGreen, SIGNAL(clicked()), Demo, SLOT(rgbUpdate()));
        QObject::connect(cbBlue, SIGNAL(clicked()), Demo, SLOT(rgbUpdate()));
        QObject::connect(pbConnect, SIGNAL(clicked()), Demo, SLOT(serialConnect()));
        QObject::connect(pushButton, SIGNAL(clicked()), Demo, SLOT(exit()));

        QMetaObject::connectSlotsByName(Demo);
    } // setupUi

    void retranslateUi(QMainWindow *Demo)
    {
        Demo->setWindowTitle(QCoreApplication::translate("Demo", "Demo", nullptr));
        pbConnect->setText(QCoreApplication::translate("Demo", "&Connect", nullptr));
        lePortName->setText(QCoreApplication::translate("Demo", "COM6", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Demo", "To FRDM-KL25Z", nullptr));
        cbRed->setText(QCoreApplication::translate("Demo", "Red", nullptr));
        cbGreen->setText(QCoreApplication::translate("Demo", "Green", nullptr));
        cbBlue->setText(QCoreApplication::translate("Demo", "Blue", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Demo", "From FRDM-KL25Z", nullptr));
        pushButton->setText(QCoreApplication::translate("Demo", "E&xit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Demo: public Ui_Demo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QSlider *horizontalSlider;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QLabel *label_7;
    QWidget *tab;
    QLabel *label_4;
    QWidget *tab_5;
    QLabel *label_9;
    QWidget *tab_2;
    QLabel *label_5;
    QWidget *tab_3;
    QLabel *label_6;
    QTabWidget *tabWidget_2;
    QWidget *tab_6;
    QLabel *label_11;
    QSlider *mesuredWidthSlider;
    QLabel *label_13;
    QLabel *label_12;
    QSlider *horizontalSlider_2;
    QLabel *label_14;
    QFrame *line;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *tab_7;
    QPushButton *pushButton_7;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit;
    QTabWidget *ConnectionTab;
    QWidget *tab_8;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QWidget *tab_9;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QLabel *label_10;
    QLabel *label_8;
    QWidget *tab_10;
    QLabel *hostLabel;
    QLabel *label_18;
    QLabel *statusLabel;
    QPushButton *getFortuneButton;
    QLineEdit *portLineEdit;
    QComboBox *hostCombo;
    QPushButton *pushButton_8;
    QMenuBar *menubar;
    QMenu *menuRelative_Depth;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(916, 583);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 99, 27));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 240, 160, 29));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setSingleStep(25);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 220, 101, 20));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(240, 0, 671, 531));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 10, 640, 480));
        label_7->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 640, 480));
        label_4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        label_9 = new QLabel(tab_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 10, 640, 480));
        label_9->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 10, 640, 480));
        label_5->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 10, 640, 480));
        label_6->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab_3, QString());
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(10, 280, 231, 251));
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        label_11 = new QLabel(tab_6);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 10, 141, 20));
        mesuredWidthSlider = new QSlider(tab_6);
        mesuredWidthSlider->setObjectName(QStringLiteral("mesuredWidthSlider"));
        mesuredWidthSlider->setGeometry(QRect(10, 30, 141, 29));
        mesuredWidthSlider->setMaximum(480);
        mesuredWidthSlider->setPageStep(40);
        mesuredWidthSlider->setSliderPosition(480);
        mesuredWidthSlider->setOrientation(Qt::Horizontal);
        label_13 = new QLabel(tab_6);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 60, 31, 17));
        label_12 = new QLabel(tab_6);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(100, 60, 51, 17));
        horizontalSlider_2 = new QSlider(tab_6);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(10, 130, 131, 29));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_14 = new QLabel(tab_6);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 100, 141, 20));
        line = new QFrame(tab_6);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 80, 231, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        lineEdit_3 = new QLineEdit(tab_6);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(160, 30, 61, 27));
        lineEdit_4 = new QLineEdit(tab_6);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(160, 130, 61, 27));
        label_15 = new QLabel(tab_6);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(100, 150, 51, 20));
        label_16 = new QLabel(tab_6);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 150, 31, 21));
        tabWidget_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        pushButton_7 = new QPushButton(tab_7);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(90, 100, 131, 27));
        label_2 = new QLabel(tab_7);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(12, 40, 131, 20));
        label_3 = new QLabel(tab_7);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 141, 21));
        lineEdit_2 = new QLineEdit(tab_7);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(152, 70, 71, 21));
        lineEdit = new QLineEdit(tab_7);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(152, 40, 71, 21));
        tabWidget_2->addTab(tab_7, QString());
        ConnectionTab = new QTabWidget(centralwidget);
        ConnectionTab->setObjectName(QStringLiteral("ConnectionTab"));
        ConnectionTab->setGeometry(QRect(10, 40, 231, 171));
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        pushButton_5 = new QPushButton(tab_8);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(0, 20, 151, 27));
        pushButton_6 = new QPushButton(tab_8);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(0, 60, 151, 27));
        pushButton_4 = new QPushButton(tab_8);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(0, 100, 151, 27));
        ConnectionTab->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QStringLiteral("tab_9"));
        pushButton_3 = new QPushButton(tab_9);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(0, 100, 171, 27));
        pushButton_2 = new QPushButton(tab_9);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(0, 70, 171, 27));
        label_10 = new QLabel(tab_9);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(170, 100, 41, 21));
        label_8 = new QLabel(tab_9);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(170, 80, 41, 17));
        ConnectionTab->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName(QStringLiteral("tab_10"));
        hostLabel = new QLabel(tab_10);
        hostLabel->setObjectName(QStringLiteral("hostLabel"));
        hostLabel->setGeometry(QRect(10, 10, 101, 17));
        label_18 = new QLabel(tab_10);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 40, 91, 21));
        statusLabel = new QLabel(tab_10);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(10, 80, 211, 17));
        getFortuneButton = new QPushButton(tab_10);
        getFortuneButton->setObjectName(QStringLiteral("getFortuneButton"));
        getFortuneButton->setGeometry(QRect(120, 110, 99, 27));
        portLineEdit = new QLineEdit(tab_10);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        portLineEdit->setGeometry(QRect(100, 40, 121, 21));
        hostCombo = new QComboBox(tab_10);
        hostCombo->setObjectName(QStringLiteral("hostCombo"));
        hostCombo->setGeometry(QRect(114, 10, 101, 27));
        ConnectionTab->addTab(tab_10, QString());
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(150, 10, 81, 27));
        MainWindow->setCentralWidget(centralwidget);
        ConnectionTab->raise();
        pushButton->raise();
        horizontalSlider->raise();
        label->raise();
        tabWidget->raise();
        tabWidget_2->raise();
        pushButton_8->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 916, 21));
        menuRelative_Depth = new QMenu(menubar);
        menuRelative_Depth->setObjectName(QStringLiteral("menuRelative_Depth"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menuRelative_Depth->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(slot1()));

        tabWidget->setCurrentIndex(4);
        tabWidget_2->setCurrentIndex(1);
        ConnectionTab->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Start", 0));
        label->setText(QApplication::translate("MainWindow", "Robot's Speed", 0));
        label_7->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Stream", 0));
        label_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Cartesian depth map", 0));
        label_9->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Time To Contact map", 0));
        label_5->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Depth visuals", 0));
        label_6->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Optic flow", 0));
        label_11->setText(QApplication::translate("MainWindow", "Mesured area width:", 0));
        label_13->setText(QApplication::translate("MainWindow", "0 px", 0));
        label_12->setText(QApplication::translate("MainWindow", "480 px", 0));
        label_14->setText(QApplication::translate("MainWindow", "Vertical position", 0));
        label_15->setText(QApplication::translate("MainWindow", "480 px", 0));
        label_16->setText(QApplication::translate("MainWindow", "0 px", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("MainWindow", "Set area", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "Confirm change", 0));
        label_2->setText(QApplication::translate("MainWindow", "Mesure area width:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Mesure area height:", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QApplication::translate("MainWindow", "Set area precisely", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Start measurement", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "Show interim result", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "End measurement", 0));
        ConnectionTab->setTabText(ConnectionTab->indexOf(tab_8), QApplication::translate("MainWindow", "Tab 1", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Show depth in realtime", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Mesure depth one time", 0));
        label_10->setText(QApplication::translate("MainWindow", "(test)", 0));
        label_8->setText(QApplication::translate("MainWindow", "(test)", 0));
        ConnectionTab->setTabText(ConnectionTab->indexOf(tab_9), QApplication::translate("MainWindow", "Tab 2", 0));
        hostLabel->setText(QApplication::translate("MainWindow", "Server name:", 0));
        label_18->setText(QApplication::translate("MainWindow", "Sever port:", 0));
        statusLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        getFortuneButton->setText(QApplication::translate("MainWindow", "Test conn.", 0));
        ConnectionTab->setTabText(ConnectionTab->indexOf(tab_10), QApplication::translate("MainWindow", "Connection", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "End", 0));
        menuRelative_Depth->setTitle(QApplication::translate("MainWindow", "Start", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

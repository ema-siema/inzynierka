//#include <QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include "mainwindow.h"
#define DEFAULT_DEVICE 0

 int main(int argv, char **args)
 {
     QApplication app(argv, args);
     MainWindow mainwindow;
    // mainwindow.robot.setupVidCaptureStream(DEFAULT_DEVICE);
     mainwindow.show();

     return app.exec();
 }

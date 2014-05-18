#include <QApplication>
#include <QTextEdit>
#include "mainwindow.h"
#define DEVICE 0

 int main(int argv, char **args)
 {
     QApplication app(argv, args);
     MainWindow mainwindow;
     mainwindow.robot.setupVidCaptureStream(DEVICE);
     mainwindow.show();

     return app.exec();
 }

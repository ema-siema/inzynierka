#include <QApplication>
#include <QTextEdit>
#include "mainwindow.h"
#define DEFAULT_DEVICE 0

//Q_DECLARE_METATYPE(cv::Mat)
 int main(int argv, char **args)
 {
     QApplication app(argv, args);
     MainWindow mainwindow;
     mainwindow.robot.setupVidCaptureStream(DEFAULT_DEVICE);
     mainwindow.show();

     return app.exec();
 }

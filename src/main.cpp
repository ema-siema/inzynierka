//#include <QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextEdit>
#include "mainwindow.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#define DEFAULT_DEVICE 0

using boost::asio::ip::tcp;


 int main(int argv, char **args)
 {
     QApplication app(argv, args);
     MainWindow mainwindow;
     //mainwindow.robot.setupVidCaptureStream(DEFAULT_DEVICE);
     mainwindow.show();

     return app.exec();
 }

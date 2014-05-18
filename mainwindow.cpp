#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "robotvision.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//the "start" button
void MainWindow::on_pushButton_clicked()
{
    robot.showWhatRobotSees();
}

//the "estimate depth" button
void MainWindow::on_pushButton_2_clicked()
{
    robot.estimateRelativeDepth();
}

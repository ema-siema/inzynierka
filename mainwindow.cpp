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
    //robot.showWhatRobotSees();

    Mat frame;
    QImage img;
    while(cvWaitKey(10)!=27){

        frame = robot.showWhatRobotSees2();
        assert(!frame.empty()); //debug
        cvtColor(frame, frame, CV_BGR2RGB);
        img = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
        ui->label_7->setPixmap(QPixmap::fromImage(img));
    }

}

//the "Mesure depth one time" button
void MainWindow::on_pushButton_2_clicked()
{
    vector <Mat> vec;
    cv::Mat rgb;
    QImage img;

    vec = robot.estimateRelativeDepth();

    rgb = vec[1];
    assert(!rgb.empty()); //debug
    img = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
    ui->label_5->setPixmap(QPixmap::fromImage(img));

    rgb = vec[0];
    assert(!rgb.empty()); //debug
    img = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
    ui->label_6->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_pushButton_3_clicked()
{
    robot.showPoorDepthInRealTime();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    robot.setRobotSpeed(value);
}

//the "End measurement" button
void MainWindow::on_pushButton_4_clicked()
{
    cv::Mat mat, rgb;
    QImage img;
    rgb = robot.showDepthMap();
    assert(!rgb.empty()); //debug
    img = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
    ui->label_4->setPixmap(QPixmap::fromImage(img));
}

//the "Confirm change" button
void MainWindow::on_pushButton_7_clicked()
{
    QString str;
    str = ui->lineEdit->text();
    robot.setMesuredAreaWidth(str.toInt());

    str = ui->lineEdit_2->text();
    robot.setMesuredAreaHeight(str.toInt());
}

//first line edit
void MainWindow::on_lineEdit_editingFinished()
{
    //robot.setMesuredAreaheight();
}

//second line edit
void MainWindow::on_lineEdit_2_editingFinished()
{

}

void MainWindow::on_mesuredWidthSlider_valueChanged(int value)
{
    robot.setMesuredAreaHeight(value);
}

void MainWindow::on_StartButton_clicked()
{


}

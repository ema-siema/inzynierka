#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "robotvision.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>
#include <cv.h>
#include <QDebug>

//#include "Source.h"

#define _ITERATOR_DEBUG_LEVEL = 2

using namespace std;
using boost::asio::ip::tcp;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	thread = new QThread();
    worker = new Worker();

	worker->moveToThread(thread);
	qRegisterMetaType< cv::Mat >("cv::Mat"); //potrzebne, ¿eby da³o siê wsadziæ cv:Mat do QT'owego SLOTa
	Q_ASSERT(connect(worker, SIGNAL(valueChanged(cv::Mat)), this, SLOT(slot1(cv::Mat))));
	connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

}

MainWindow::~MainWindow()
{
	worker->abort();
    thread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    
	delete thread;
    delete worker;
    delete ui;
}

void MainWindow::slot1(cv::Mat value){
	qDebug()<<"slot1()";
	//imshow("server", value);
	QImage img = QImage((const unsigned char*)(value.data), value.cols, value.rows, QImage::Format_RGB888);
    ui->label_7->setPixmap(QPixmap::fromImage(img));
}

//the "start" button
void MainWindow::on_pushButton_clicked()
{

    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.

    worker->requestWork();
}

//the "Mesure depth one time" button
void MainWindow::on_pushButton_2_clicked()
{
    vector <Mat> vec;
    cv::Mat rgb, frame1, frame2, frame;
    QImage img;

//    frame1 = robot.captureFrame();
    robot.capt >>  frame1;
    cout<< "estimateRelativeDepth(): measure started" << endl;

    //cvNamedWindow("flow1", CV_WINDOW_AUTOSIZE); //todo del
    //imshow("flow1", frame1);//todo del

    while(true){

        frame = robot.showWhatRobotSees2();
        assert(!frame.empty()); //debug
        cvtColor(frame, frame, CV_BGR2RGB);
        img = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
        ui->label_7->setPixmap(QPixmap::fromImage(img));
        //cout << "mesure depth one time" <<endl;
        if(cvWaitKey(10)==27) break;
    }
    cout<< "estimateRelativeDepth(): measure ended" << endl;

    cvtColor(frame, frame, CV_RGB2BGR);

    cvNamedWindow("flow2", CV_WINDOW_AUTOSIZE); //todo del
    imshow("flow2", frame);//todo del

    vec = robot.estimateRelativeDepth(frame1, frame);

    rgb = vec[1];
    robot.drawFOE(robot.findFOE(), rgb);
    cout <<"debugeiro"<<endl;
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

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    robot.setMesuredAreaVerticalPosition(value);
}

//the "End measurement" button
void MainWindow::on_pushButton_4_clicked()
{
    cv::Mat mat, rgb, frame, frame1, frame2, flow;
    QImage img;
    vector <Mat> vec;
    pair <int, int> foe;
    robot.capt >>  frame;

    cout<< "on_pushButton_4_clicked(): measure ended" << endl;
    robot.setLastDepthFrame(frame);

    robot.getLastDepthFrame().copyTo(frame2);
    robot.getInitialDepthFrame().copyTo(frame1);

	//imshow("frame1", frame1);
	//imshow("frame2", frame2);
	//imwrite("frame1.jpg", frame1);
	//imwrite("frame2.jpg", frame2);

    assert(!frame1.empty()); //debug
    assert(!frame2.empty()); //debug

    vec = robot.estimateRelativeDepth(frame1, frame2);
	cout << "juz po estimate" <<endl;
    rgb = vec[1];
    robot.drawFOE(robot.findFOE(), rgb);    //todo change findFOE to some getFOE
    assert(!rgb.empty()); //debug
    img = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
    ui->label_5->setPixmap(QPixmap::fromImage(img));

    rgb = vec[0];
    assert(!rgb.empty()); //debug
    img = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
    ui->label_6->setPixmap(QPixmap::fromImage(img));

    rgb = vec[2];
    assert(!rgb.empty()); //debug
    img = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
    ui->label_9->setPixmap(QPixmap::fromImage(img));


    //draw plot in the "Cartesian Depth Map" tab

	rgb = vec[3];
    //rgb = robot.showDepthMap(); //to by³o w wersji sprzed przenosin -> CZEMU???!
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

//the 'start measurement' button
void MainWindow::on_pushButton_5_clicked()
{
    Mat frame;
    robot.capt >>  frame;
    cout<< "on_pushButton_5_clicked(): measure started" << endl; //debug

    robot.setInitialDepthFrame(frame);
}

//void MainWindow::onProgressChagned()
//{
//	Mat m = img;
//	cout << "slot slot slot " << endl; 
//    //cvtColor(m, m, CV_BGR2RGB);
//    //QImage img = QImage((const unsigned char*)(m.data), m.cols, m.rows, QImage::Format_RGB888);
//    //ui->label_7->setPixmap(QPixmap::fromImage(img));
//}
#include "mainwindow.h"
#include "C:\Users\User\Documents\projekty\inzynierka\testt3\GeneratedFiles\ui_mainwindow.h"
#include <iostream>
#include "robotvision.h"
//#include <QtNetwork>
#include <QDebug>
#include <QtWidgets/QMainWindow>
#define _ITERATOR_DEBUG_LEVEL = 2

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
	cout <<"on_pushButton_clicked()"<<endl;

    //robot.showWhatRobotSees();
	cout << "sztart" <<endl;
    Mat frame;
    QImage img;
    while(!waitKey(0)){
		cout << "ke?" <<endl;
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
    cv::Mat rgb, frame1, frame2, frame;
    QImage img;

//    frame1 = robot.captureFrame();
    robot.capt >>  frame1;
    cout<< "estimateRelativeDepth(): measure started" << endl;

    cvNamedWindow("flow1", CV_WINDOW_AUTOSIZE); //todo del
    imshow("flow1", frame1);//todo del

    while(true){

        frame = robot.showWhatRobotSees2();
        assert(!frame.empty()); //debug
        cvtColor(frame, frame, CV_BGR2RGB);
        img = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
        ui->label_7->setPixmap(QPixmap::fromImage(img));
        cout << "mesure depth one time" <<endl;
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
    ///robot.showPoorDepthInRealTime();
    requestNewFortune();

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    robot.setRobotSpeed(value);
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
    //rgb = robot.showDepthMap(); //to by�o w wersji sprzed przenosin -> CZEMU???!
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
	//here
    robot.setInitialDepthFrame(frame);
	QImage img = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
	    ui->label_6->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::requestNewFortune()
{
	qDebug() << "requestNewFortune()"; //debug

}

void MainWindow::readFortune()
{
	qDebug() << "blockSize2: " << (int)blockSize;
}

void MainWindow::sessionOpened()
{
    cout<< "sessionOpened()" << endl; //debug

//    ui->statusLabel->setText(tr("This examples requires that you run the "
//                            "Fortune Server example as well."));


    //enableGetFortuneButton();
}

void MainWindow::on_getFortuneButton_clicked()
{
    requestNewFortune();
}

void MainWindow::slot1(){//dobre i dzialajace, ale tylko lokalnie
	Mat frame;
    QImage img;
	frame = robot.showWhatRobotSees2();
	cvtColor(frame, frame, CV_BGR2RGB);
    img = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
	ui->label_7->setPixmap(QPixmap::fromImage(img));
}

/*
void MainWindow::slot1(){
	//Mat frame;
    //QImage img;
	requestNewFortune();
	timer->stop();
	//frame = robot.showWhatRobotSees2();
	//cvtColor(frame, frame, CV_BGR2RGB);
    //img = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
	//ui->label_7->setPixmap(QPixmap::fromImage(img));
}*/

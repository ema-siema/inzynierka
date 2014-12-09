#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "robotvision.h"
#include <QtNetwork>
#include <QDebug>
#include <QtWidgets/QMainWindow>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        ui->hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            ui->hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QString("localhost"))
        ui->hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            ui->hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            ui->hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    tcpSocket = new QTcpSocket(this);

//    connect(hostCombo, SIGNAL(editTextChanged(QString)),
//            this, SLOT(enableGetFortuneButton()));
//    connect(portLineEdit, SIGNAL(textChanged(QString)),
//            this, SLOT(enableGetFortuneButton()));
//    connect(getFortuneButton, SIGNAL(clicked()),
//            this, SLOT(requestNewFortune()));
//    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));

//    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
//            this, SLOT(displayError(QAbstractSocket::SocketError)));
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

//the "start" button
void MainWindow::on_pushButton_clicked()
{
	cout <<"on_pushButton_clicked()"<<endl;

	timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(slot1()));
    timer->start(250); //time specified in ms
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

    vec = robot.estimateRelativeDepth(frame1, frame2);

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
//the 'start measurement' button
void MainWindow::on_pushButton_5_clicked()
{
	    cout<< "on_pushButton_5_clicked(): measure started" << endl; //debug
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

    //ui->getFortuneButton->setEnabled(false);
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->hostCombo->currentText(),
                             ui->portLineEdit->text().toInt());

}

void MainWindow::readFortune()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint32))
            return;

        in >> blockSize;
        qDebug() << "blockSize: " << (int)blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;

		qint64 imagesInQue = tcpSocket->bytesToWrite()/blockSize;
    int maxPendingImages = 10;
    if(imagesInQue > maxPendingImages)
    {
        std::cout << "Dumping." << std::endl;
        return;
    }

    QImage nextImage;
    in >> nextImage;


	//qDebug() << "blockSize2: " << (int)blockSize;
    //currentImage = nextImage;
    ///ui->statusLabel->setText(currentFortune);
    ui->label_6->setPixmap(QPixmap::fromImage(nextImage));
    //getFortuneButton->setEnabled(true);
}

void MainWindow::sessionOpened()
{
    cout<< "sessionOpened()" << endl; //debug

    // Save the used configuration

    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

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
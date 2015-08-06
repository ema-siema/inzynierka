
#include "Source.h"
#include <QTimer>
#include <QEventLoop>

#include <QThread>
#include <QDebug>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>

#include <cv.h>

using boost::asio::ip::tcp;
using namespace cv;

Mat img = Mat::zeros(640, 480, CV_8UC3);

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void servershow(){

}

void Worker::doWork()
{
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();


	try{
        boost::asio::io_service io_service;
        boost::array<char, 921600> buf;         /* the size of reciev mat frame is caculate by 320*240*3 */
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3200));

        for (int i = 0; i < 60; i ++){

				mutex.lock();
				bool abort = _abort;
				mutex.unlock();

				if (abort) {
					qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
					break;
				}

				tcp::socket socket(io_service);
				acceptor.accept(socket);
				boost::system::error_code error;
				size_t len = socket.read_some(boost::asio::buffer(buf), error);
				std::cout<<"get data length :"<<len<<endl; /* disp the data size recieved */
				std::vector<uchar> vectordata(buf.begin(),buf.end()); /* change the recieved mat frame(1*230400) to vector */
				cv::Mat data_mat(vectordata,true);

				img = data_mat.reshape(3,480);       /* reshape to 3 channel and 240 rows */
				//cout<<"reshape over"<<endl;
				//emit SigUpdateTransmissionWindow();

				    // cvtColor(frame, frame, CV_BGR2RGB);

				        // This will stupidly wait 1 sec doing nothing...
				QEventLoop loop;
				QTimer::singleShot(100, &loop, SLOT(quit()));
				loop.exec();

				// Once we're done waiting, value is updated
				emit valueChanged(QString::number(i));	
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finished();
}

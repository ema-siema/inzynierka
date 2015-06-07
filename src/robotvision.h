/*Class for managing all computer vision. It contains camera stream,
and methods that execute operations on the stream.

How to use it:

    1.create RobotVision object, for example:

        RobotVision robot;

    2.setup stream

        robot.setupVidCaptureStream(DEVICE);

    3.execute methods you like

        robot.showWhatRobotSees();
*/

#ifndef ROBOTVISION_H
#define ROBOTVISION_H

#include <iostream>
//#include <cv.h>
//#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>
#include <stdlib.h>
//#include <QtNetwork>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QtWidgets/QLabel>

#define DEFAULT_X 640

using namespace std;
using namespace cv;

class RobotVision
{
private:

    int device_id;
    double robotSpeed;
    int mesuredAreaWidth;
    int mesuredAreaHeight;
    int mesuredAreaVerticalPosition;
    Mat initialDepthFrame;
    Mat lastDepthFrame;

public:
    VideoCapture capt;
    pair <int, int> FOE; // first = x, second = y

    RobotVision();

    vector <Mat> estimateRelativeDepth(Mat frame1, Mat frame2);
    void estimateRelativeDepth(Mat frame1, Mat frame2, Mat &pRelDepth);
    int showWhatRobotSees();
    Mat showWhatRobotSees2();
    cv::Mat captureFrame();
    void setupVidCaptureStream(int _device_id);
    void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color);
    void drawPoorDepth(Mat& flow, Mat& dflowmap, Mat &ttcMap, vector< vector<double> > &ttcmatrix, int step);
    void showPoorDepthInRealTime();
    cv::Mat showDepthMap();
    cv::Mat drawPlotAxes();
    Rect createRectangleForMesuredArea();
    pair <int, int> findFOE();
    void drawFOE(pair <int, int> foe, Mat &frame);
    double calcDistanceFromFOE(int x, int y);
	//QBasicTimer m_timer;
	//void timerEvent(QTimerEvent * ev);
	void tick(QLabel *label);

    //getters and setters
    int getMesuredAreaWidth() const;
    void setMesuredAreaWidth(int value);

    int getMesuredAreaHeight() const;
    void setMesuredAreaHeight(int value);

    double getRobotSpeed() const;
    void setRobotSpeed(double value);

    Mat getInitialDepthFrame() const;
    void setInitialDepthFrame(const Mat &value);

    Mat getLastDepthFrame() const;
    void setLastDepthFrame(const Mat &value);

    int getMesuredAreaVerticalPosition() const;
    void setMesuredAreaVerticalPosition(int value);
};

#endif // ROBOTVISION_H

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
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

class RobotVision
{
private:

    int device_id;
    double robotSpeed;
    int mesuredAreaWidth;
    int mesuredAreaHeight;

public:

    VideoCapture capt;
    RobotVision();
    vector <Mat> estimateRelativeDepth(Mat frame1, Mat frame2);
    void estimateRelativeDepth(Mat frame1, Mat frame2, Mat &pRelDepth);
    int showWhatRobotSees();
    Mat showWhatRobotSees2();
    cv::Mat captureFrame();
    void setupVidCaptureStream(int _device_id);
    void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color);
    void drawPoorDepth(Mat& flow, Mat& dflowmap, int step);
    void showPoorDepthInRealTime();
    cv::Mat showDepthMap();
    double getRobotSpeed() const;
    void setRobotSpeed(double value);
    cv::Mat drawPlotAxes();
    Rect createRectangleForMesuredArea();

    //getters and setters
    int getMesuredAreaWidth() const;
    void setMesuredAreaWidth(int value);
    int getMesuredAreaHeight() const;
    void setMesuredAreaHeight(int value);

};

#endif // ROBOTVISION_H

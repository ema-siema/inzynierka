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

public:

    VideoCapture capt;
    RobotVision();
    void estimateRelativeDepth();
    void estimateRelativeDepth(Mat frame1, Mat frame2, Mat &pRelDepth);
    int showWhatRobotSees();
    Mat captureFrame();
    void setupVidCaptureStream(int _device_id);
    void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color);
    void drawPoorDepth(Mat& flow, Mat& dflowmap, int step);
    void showPoorDepthInRealTime();

    double getRobotSpeed() const;
    void setRobotSpeed(double value);
};

#endif // ROBOTVISION_H

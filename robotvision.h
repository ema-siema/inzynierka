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
public:
    VideoCapture capt;
    RobotVision();
    void estimateRelativeDepth();
    int showWhatRobotSees();
    Mat captureFrame();
    void setupVidCaptureStream(int _device_id);
    void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color);
    void drawPoorDepth(Mat& flow, Mat& dflowmap, int step);

};

#endif // ROBOTVISION_H

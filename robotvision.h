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
};

#endif // ROBOTVISION_H

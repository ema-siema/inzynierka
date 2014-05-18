#include "robotvision.h"
#include <cv.h>

using namespace cv;

RobotVision::RobotVision()
{
    device_id = 0;
}

void RobotVision::estimateRelativeDepth(){
    //given two frames, it depicts imprecise relative depth basing on optical flow

    Mat frame1, frame2;

    frame1 = captureFrame();
    usleep(250000); //TODO do sth better...
    frame2 = captureFrame();

    cout << "void estimateRelativeDepth()" << endl;
}

int RobotVision::showWhatRobotSees(){
    Mat frame1, frame2;
    cvNamedWindow("Camera_Output", CV_WINDOW_AUTOSIZE); //Create window

    capt >> frame1; // get a new frame from camera
    imshow("Camera_Output", frame1);
    usleep(250000); //TODO do sth better...

    while(cvWaitKey(33) != 27){

        capt >> frame1; // get a new frame from camera
        imshow("Camera_Output", frame1);
        usleep(250000); //TODO do sth better...
        capt >> frame2; // get a new frame from camera
        imshow("Camera_Output", frame2);
    }

    cvDestroyAllWindows();
    return 0;
}

Mat RobotVision::captureFrame(){
    Mat frame;

    capt >> frame;

    return frame;
}

void RobotVision::setupVidCaptureStream(int _device_id){
    // credits to: http://stackoverflow.com/questions/9356987/opencv-videocapture-wrapper-class
    device_id = _device_id;
    capt = cv::VideoCapture(device_id);

    cout << "Checking device" << endl;
    if(!capt.isOpened()){
        cout << "Couldn't open device" << endl;
        return;
    }
    else{
        cout << "Device opened " << endl;
    }
}

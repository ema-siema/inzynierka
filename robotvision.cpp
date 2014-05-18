#include "robotvision.h"
#include <cv.h>
#include <assert.h>

#define SCALE_FACTOR 5

using namespace cv;

RobotVision::RobotVision()
{
    device_id = 0;
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

void RobotVision::drawOptFlowMap (const Mat& flow, Mat& cflowmap, int step, const Scalar& color) {
//taken from Gunnar Farneback example in opencv directory
    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 color);
            circle(cflowmap, Point(cvRound(x+fxy.x), cvRound(y+fxy.y)), 1, color, -1);
        }
}

double flowVectorLength( Point2f& fxy ){

    return ( sqrt( (fxy.x)*(fxy.x) + (fxy.y)*(fxy.y) ) );
}

void RobotVision::drawPoorDepth ( Mat& flow, Mat& dflowmap, int step) {
    int len;
    for(int y = 0; y < dflowmap.rows; y += step)
        for(int x = 0; x < dflowmap.cols; x += step)
        {
            Point2f& fxy = flow.at<Point2f>(y, x);

            Vec3b color = flow.at<Vec3b>(Point(x,y));

            //dflowmap.at<Point2f>(y, x);
            len=flowVectorLength(fxy);
            ///cout << "heheszki" << len <<endl;
            //Point3_<uchar>* p = flow.ptr<Point3_<uchar> >(y,x);
            //cout << "debugos1 " << flow.at<cv::Vec3b>(y,x)[0]  << endl;

            ///cout << "debugos1 " << (int)color[0]  << endl;
            ///cout << "debugos2 " << (int)color[1]  << endl;
            ///cout << "debugos3 " << (int)color[2]  << endl;
            color[0] = len*SCALE_FACTOR;
            color[1] = len*SCALE_FACTOR;
            color[2] = len*SCALE_FACTOR;
            dflowmap.at<Vec3b>(Point(x,y)) = color;

            //line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)), color);
            //circle(cflowmap, Point(cvRound(x+fxy.x), cvRound(y+fxy.y)), 1, color, -1);
        }
}

void RobotVision::estimateRelativeDepth(){
    //given two frames, it depicts imprecise relative depth basing on optical flow

    Mat frame1, frame2, gray1, gray2, flow, cflow, dflow;

    frame1 = captureFrame();
    usleep(250000); //TODO do sth better...
    frame2 = captureFrame();
    cvtColor(frame1, gray1, COLOR_BGR2GRAY);
    cvtColor(frame2, gray2, COLOR_BGR2GRAY);

    calcOpticalFlowFarneback(gray1, gray2, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    cvtColor(gray1, cflow, COLOR_GRAY2BGR);
    cvtColor(gray2, dflow, COLOR_GRAY2BGR);
    drawOptFlowMap(flow, cflow, 8, Scalar(0, 255, 0));
    drawPoorDepth(flow, dflow, 1);

    assert(!flow.empty()); //debug
    assert(!cflow.empty()); //debug

    cvNamedWindow("Camera_Output2", CV_WINDOW_AUTOSIZE);
    imshow("Camera_Output2", cflow);

    cvNamedWindow("Camera_Output2,1", CV_WINDOW_AUTOSIZE);
    imshow("Camera_Output2,1", dflow);

    cout << "void estimateRelativeDepth()" << endl; //debug
}

/*captures frame from "capt" stream in RobotVision object*/
Mat RobotVision::captureFrame(){
    Mat frame;

    capt >> frame;

    return frame;
}

/*If there is only one camera, set _device_id to 0*/
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

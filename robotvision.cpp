#include "robotvision.h"
#include <cv.h>
#include <assert.h>
#include <vector>

#define SCALE_FACTOR 5
#define STANDARD_FRAME_WIDTH 640 //in pixels
#define STANDARD_FRAME_HEIGHT 480


///global robotSpeed = 0; //todo: mock for robot's speed

using namespace cv;

double RobotVision::getRobotSpeed() const
{
    return robotSpeed;
}

void RobotVision::setRobotSpeed(double value)
{
    robotSpeed = value;
}

int RobotVision::getMesuredAreaWidth() const
{
    return mesuredAreaWidth;
}

void RobotVision::setMesuredAreaWidth(int value)
{
    mesuredAreaWidth = value;
}

int RobotVision::getMesuredAreaHeight() const
{
    return mesuredAreaHeight;
}

void RobotVision::setMesuredAreaHeight(int value)
{
    mesuredAreaHeight = value;
}

RobotVision::RobotVision()
{
    device_id = 0;
    robotSpeed = 0;
    mesuredAreaHeight = STANDARD_FRAME_HEIGHT;
    mesuredAreaWidth = STANDARD_FRAME_WIDTH;
}

int RobotVision::showWhatRobotSees(){
    Mat frame1;
    cvNamedWindow("Camera_Output", CV_WINDOW_AUTOSIZE); //Create window
    Rect rect;

    while(cvWaitKey(10)!=27){

        capt >> frame1; // get a new frame from camera
//        rect = createRectangleForMesuredArea();
//        rectangle(frame1, rect, Scalar(0, 0, 0));
        imshow("Camera_Output", frame1);

    }

    cvDestroyAllWindows();
    return 0;
}

Mat RobotVision::showWhatRobotSees2(){
    // This function varies from int RobotVision::showWhatRobotSees()
    // It doesn't use imshow in a loop, but returns current frame.
    // This function is meant to be used in a extern loop.

    Mat frame;
    Rect rect;

    capt >> frame; // get a new frame from camera
    rect = createRectangleForMesuredArea();
    rectangle(frame, rect, Scalar(0, 0, 0));

    return frame;
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

/*draws inacurate depth on dflowmap for user interface purposes.
Is meant to be used with some imshow() functions .*/

void RobotVision::drawPoorDepth ( Mat& flow, Mat& dflowmap, int step) {

    int len;

    for(int y = 0; y < dflowmap.rows; y += step)
        for(int x = 0; x < dflowmap.cols; x += step)
        {
            Point2f& fxy = flow.at<Point2f>(y, x);
            Vec3b color = flow.at<Vec3b>(Point(x,y));

            len=flowVectorLength(fxy);

            color[0] = len*SCALE_FACTOR;    //todo maybe use some nonlinear function for pixel brightness setting?
            color[1] = len*SCALE_FACTOR;
            color[2] = len*SCALE_FACTOR;
            dflowmap.at<Vec3b>(Point(x,y)) = color;
        }
}

//given two frames, it depicts imprecise relative depth basing on optical flow

Rect RobotVision::createRectangleForMesuredArea(){

    int x = 0,
        y = (STANDARD_FRAME_HEIGHT - this->mesuredAreaHeight)/2,
        width = STANDARD_FRAME_WIDTH,
        height = this->mesuredAreaHeight/2;

    cout << "createRectangleForMesuredArea " << y << endl;
    return Rect(x, y, width, height);
}

vector <Mat> RobotVision::estimateRelativeDepth(){

    vector <Mat> vec;
    Mat frame1, frame2, gray1, gray2, flow, cflow, dflow;

    frame1 = captureFrame();
    usleep(250000); //TODO do sth better... it should be connected with robot's speed
    frame2 = captureFrame();

    Rect rect = createRectangleForMesuredArea();

    frame1 = frame1(rect);
    frame2 = frame2(rect);

    cvtColor(frame1, gray1, COLOR_BGR2GRAY);
    cvtColor(frame2, gray2, COLOR_BGR2GRAY);

    calcOpticalFlowFarneback(gray1, gray2, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    cvtColor(gray1, cflow, COLOR_GRAY2BGR);
    cvtColor(gray2, dflow, COLOR_GRAY2BGR);
    drawOptFlowMap(flow, cflow, 8, Scalar(0, 255, 0));
    drawPoorDepth(flow, dflow, 1);

    assert(!flow.empty()); //debug
    assert(!cflow.empty()); //debug

    //not needed anymore since the plot is shown in QLabel
    //cvNamedWindow("Camera_Output2", CV_WINDOW_AUTOSIZE);
    //imshow("Camera_Output2", cflow);

    //cvNamedWindow("Camera_Output2,1", CV_WINDOW_AUTOSIZE);
    //imshow("Camera_Output2,1", dflow);

    vec.push_back(cflow);
    vec.push_back(dflow);

    cout << "void estimateRelativeDepth()" <<" totreo " << endl; //debug

    return vec;
}

//given two frames, it depicts imprecise relative depth basing on optical flow
void RobotVision::estimateRelativeDepth(Mat frame1, Mat frame2, Mat &pRelDepth){

    Mat gray1, gray2, flow, cflow;

    cvtColor(frame1, gray1, COLOR_BGR2GRAY);
    cvtColor(frame2, gray2, COLOR_BGR2GRAY);

    calcOpticalFlowFarneback(gray1, gray2, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    cvtColor(gray1, cflow, COLOR_GRAY2BGR);
    drawOptFlowMap(flow, cflow, 8, Scalar(0, 255, 0));
    drawPoorDepth(flow, pRelDepth, 1);

    assert(!cflow.empty()); //debug
    assert(!pRelDepth.empty()); //debug

    cout << "void estimateRelativeDepth()" <<" what!??"<< endl; //debug
}

void RobotVision::showPoorDepthInRealTime(){
    Mat frame1, frame2, result;
    cvNamedWindow("Camera_Output_D", CV_WINDOW_AUTOSIZE); //Create window

    while(cvWaitKey(10)!=27){

        if(getRobotSpeed()!=0){
            capt >> frame1; // get a new frame from camera
            usleep(250000); //TODO do sth better...
            capt >> frame2; // get a new frame from camera
            frame2.copyTo(result);
            estimateRelativeDepth(frame1, frame2, result);
            assert(!result.empty());
            imshow("Camera_Output_D", result);
        }
    }

    cvDestroyAllWindows();
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

cv::Mat RobotVision::showDepthMap(){
    Mat mat;
    mat = drawPlotAxes();
    assert(!mat.empty()); //debug
    return mat;
}

cv::Mat RobotVision::drawPlotAxes(){
    int left = 10, down = 470, right = 630, up = 10;
    int step = 50;
    Scalar black(0,0,0);
    Scalar white(254,254,254);

    Mat plot(480, 640, CV_8UC3, white);
    putText(plot, "Distance (meters)", Point(left, up), FONT_HERSHEY_PLAIN, 1.0, black);
    putText(plot, "Angle (deegres)", Point(right-130, down-20), FONT_HERSHEY_PLAIN, 1.0, black);
    //cvNamedWindow("Depth plot", CV_WINDOW_AUTOSIZE);
    //imshow("Dvoidepth plot", plot); //not needed anymore since the plot is shown in QLabel
    line(plot, Point(left, down), Point(right, down), black);
    line(plot, Point(left, down), Point(left, up), black);

    for(int height = down; height >= up; height -= step){
        line(plot, Point(left-5, height), Point(left+5, height), black);
    }

    for(int width = left; width <= right; width += step){
        line(plot, Point(width, down+5), Point(width, down-5), black);
    }

    return plot;
}

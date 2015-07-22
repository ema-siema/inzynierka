#include "robotvision.h"
#include <cv.h>
#include <assert.h>
#include <vector>
#include <windows.h>
#include <fstream>

#define SCALE_FACTOR 5
#define STANDARD_FRAME_WIDTH 640 //in pixels
#define STANDARD_FRAME_HEIGHT 480


///global robotSpeed = 0; //todo: mock for robot's speed

using namespace cv;

double RobotVision::getRobotSpeed() const{
    return robotSpeed;
}

void RobotVision::setRobotSpeed(double value){
    robotSpeed = value;
}

int RobotVision::getMesuredAreaWidth() const{
    return mesuredAreaWidth;
}

void RobotVision::setMesuredAreaWidth(int value){
    mesuredAreaWidth = value;
}

int RobotVision::getMesuredAreaHeight() const
{
    return mesuredAreaHeight;
}

void RobotVision::setMesuredAreaHeight(int value)
{
    mesuredAreaHeight = value;
	//estimationXCoordinate = this->mesuredAreaVerticalPosition + this->mesuredAreaHeight/2;
}


Mat RobotVision::getInitialDepthFrame() const
{
    return initialDepthFrame;
}

void RobotVision::setInitialDepthFrame(const Mat &value)
{
    initialDepthFrame = value;
}

Mat RobotVision::getLastDepthFrame() const
{
    return lastDepthFrame;
}

void RobotVision::setLastDepthFrame(const Mat &value)
{
    lastDepthFrame = value;
}

int RobotVision::getMesuredAreaVerticalPosition() const
{
    return mesuredAreaVerticalPosition;
}

void RobotVision::setMesuredAreaVerticalPosition(int value)
{
    //mesuredAreaVerticalPosition = value;
	//estimationXCoordinate = this->mesuredAreaVerticalPosition + this->mesuredAreaHeight/2;
	estimationXCoordinate = value;
}

RobotVision::RobotVision()
{
    device_id = 0;
    robotSpeed = 0;
    mesuredAreaHeight = STANDARD_FRAME_HEIGHT;
    mesuredAreaWidth = STANDARD_FRAME_WIDTH;
	mesuredAreaVerticalPosition = 0;
	estimationXCoordinate = 0;
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
    rectangle(frame, rect, Scalar(0, 255, 0));
	line(frame, Point(0, estimationXCoordinate),  Point(640, estimationXCoordinate),  Scalar(255,0,0)); //red line on ttcMap


    return frame;
}

void RobotVision::drawOptFlowMap (const Mat& flow, Mat& cflowmap, int step, const Scalar& color) {
//Taken from Gunnar Farneback example in opencv directory.

    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);

            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 color);
            circle(cflowmap, Point(cvRound(x+fxy.x), cvRound(y+fxy.y)), 1, color, -1);
        }

}

double RobotVision::calcDistanceFromFOE(int x, int y){
    int fx, fy; //FOE x & FOE y
    double fxd, fyd, xd, yd;
    double result, temp, temp2;

    fx = FOE.first;
    fy = FOE.second;

    fxd = (double)fx;
    fyd = (double)fy;
    xd = (double)x;
    yd = (double)y;

    temp = abs( fxd - xd );
    temp2  = abs(fyd - yd);
    //cout <<"x: "<< xd <<"fx: "<< fx<<" y: "<<yd <<" fy: "<<fy <<" temp: "<<temp<<" temp2: "<< temp2 << endl;

    result = temp*temp + temp2*temp2;
    result = sqrt(result);

    return result;
}

double calcFlowVectorLength( Point2f fxy ){

    return ( sqrt( (fxy.x)*(fxy.x) + (fxy.y)*(fxy.y) ) );
}

/*draws inacurate depth on dflowmap for user interface purposes.
Is meant to be used with some imshow() functions .*/

void RobotVision::drawPoorDepth ( Mat &flow, Mat &dflowmap, Mat &ttcMap, vector< vector<double> > &ttcmatrix, int step) {
    //Modified to additionally estimate TTC
	cout << "drawPoorDepth()" << endl;
    double distanceFromFOE, flowVectorLength, TTC, max;
    max = 0;
	assert(!flow.empty());
	assert(!dflowmap.empty());
	assert(!ttcMap.empty());
	cout << "dflowmap" << dflowmap.rows<<endl;
	cout << "dflowmap" << dflowmap.cols<<endl;
	cout << "step" << step;
    int debugCounter=0;

	for(int y = 0; y < dflowmap.rows; y += step)
        for(int x = 0; x < dflowmap.cols; x += step)
        {
            Point2f fxy = flow.at<Point2f>(y, x);
            Vec3b color = flow.at<Vec3b>(Point(x,y));
			debugCounter++;
            flowVectorLength = calcFlowVectorLength(fxy);
            //cout << "flowVectorLength: " << flowVectorLength << endl;
			//cout << "debugCounter: " << debugCounter << endl;
            distanceFromFOE = calcDistanceFromFOE(x, y);
            //cout << "distanceFromFOE: " << distanceFromFOE << endl;

            if(flowVectorLength < 1) flowVectorLength=0;

            //cout << "TTC: " << distanceFromFOE/flowVectorLength << endl;
            if(flowVectorLength != 0 ) TTC = distanceFromFOE/flowVectorLength;
            else TTC = -1;
            //cout <<" TTC "<< TTC <<endl;
            if(TTC > max) max = TTC;
            ttcmatrix[x][y] = TTC;

            //color[0] = flowVectorLength*SCALE_FACTOR;
            //color[1] = flowVectorLength*SCALE_FACTOR;
            //color[2] = flowVectorLength*SCALE_FACTOR;
            //dflowmap.at<Vec3b>(Point(x,y)) = color;
		}

    cout << "max: " << max<< endl;
}

//given two frames, it depicts imprecise relative depth basing on optical flow

Rect RobotVision::createRectangleForMesuredArea(){

    int x = 0,
    //y = (STANDARD_FRAME_HEIGHT - this->mesuredAreaHeight)/2,
    y = this->getMesuredAreaVerticalPosition(),
	width = STANDARD_FRAME_WIDTH,
    height = this->mesuredAreaHeight,
	yMax = STANDARD_FRAME_HEIGHT - this->mesuredAreaHeight;

	//cout << "elo " << yMax << " " << y << " "<< this->getMesuredAreaVerticalPosition() << " " <<endl;
	//y = y + this->getMesuredAreaVerticalPosition();
	if(y >= yMax){
		y = yMax-1;
	}
	if(y <= 0){
		y = 0;
    }

    //cout << "createRectangleForMesuredArea " << y << endl; //debug
    return Rect(x, y, width, height);
}

void drawTTCMap( Mat &map, vector< vector<double> > TTCMatrix, int size){
    double max = 0, TTC;
    int col;
    Vec3b color = map.at<Vec3b>(Point(1,1));

    for(int x=0; x<640; x++)
        for(int y=0; y<size; y++ ){
           if(TTCMatrix[x][y] > max ) max = TTCMatrix[x][y];
           //cout<< "TTCMatrix"<<TTCMatrix[y][x] << endl;
        }

    cout <<"maxo"<<max<<endl;
    max=2*max;
	if(max<=0) {
		max = 1;
	}

    for(int x=0; x<640; x++)
        for(int y=0; y<size; y++ ){

           if(TTCMatrix[x][y] == -1 ) TTCMatrix[x][y] = max;
           col = 255*TTCMatrix[x][y]/max;
           //cout << "col " << col <<endl;

           color[0] = 255-col;    //todo maybe use some nonlinear function for pixel brightness setting?
           color[1] = 255-col;
           color[2] = 255-col;
           map.at<Vec3b>(Point(x,y)) = color;
        }
}


vector <Mat> RobotVision::estimateRelativeDepth(Mat frame1, Mat frame2){
    vector <Mat> vec;
    Mat gray1, gray2, flow, cflow, dflow, eflow, ttcMap, plot;
    //double ttcmatrix[getMesuredAreaHeight()][640];
    //usleep(1000000); //TODO do sth better... it should be connected with robot's speed
	int num_of_col = 640;
    int num_of_row = getMesuredAreaHeight();
    double init_value = 0;
	cout << "estimate raz " <<endl;
    vector< vector<double> > ttcmatrix;
    ttcmatrix.resize( num_of_col , vector<double>( num_of_row , init_value ) );
	ttcmatrix.resize( num_of_col , vector<double>( num_of_row , init_value ) );

	Rect rect = createRectangleForMesuredArea();    //TODO change the word 'rectangle' for 'borders' maybe?
		cout << "estimate dwa " <<endl;

    frame1 = frame1(rect);
    frame2 = frame2(rect);

    cvtColor(frame1, gray1, COLOR_BGR2GRAY);
    cvtColor(frame2, gray2, COLOR_BGR2GRAY);
		cout << "estimate tszy " <<endl;

    calcOpticalFlowFarneback(gray1, gray2, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
	cout << "estimate cztery " <<endl;

    cvtColor(gray1, cflow, COLOR_GRAY2BGR);
    cvtColor(gray2, dflow, COLOR_GRAY2BGR);
    dflow.copyTo(eflow);
    dflow.copyTo(ttcMap);//todo learn how to initialize the "cv::Map ttcMap"
    //dflow.copyTo(plot);
    plot=drawPlotAxes();
	cout << "estimate pierc " <<endl;

    this->findFOE();
		cout << "estimate pierc i pol" <<endl;

    drawOptFlowMap(flow, eflow, 8, Scalar(0, 255, 0));
		cout << "estimate pierc i czy tszwarte " <<endl;

    drawPoorDepth(flow, dflow, ttcMap, ttcmatrix, 1);
	cout << "estimate szesc " <<endl;

    cout << "ttcmatrix[1][1]: " << ttcmatrix[1][1] << endl;

    drawTTCMap(ttcMap, ttcmatrix, getMesuredAreaHeight());
		cout << "estimate siem " <<endl;

    assert(!flow.empty()); //debug
    assert(!cflow.empty()); //debug
    assert(!eflow.empty()); //debug
    assert(!ttcMap.empty()); //debug
	cout << "estimate 8 " <<endl;

	double minTemp = 100000000, maxTemp = 0, tempFactor = 0; 

	for(int i=0; i<640; i++){
		if(ttcmatrix[i][estimationXCoordinate] > maxTemp){
			maxTemp = ttcmatrix[i][estimationXCoordinate];
		}
		if(ttcmatrix[i][estimationXCoordinate] < minTemp){
			minTemp = ttcmatrix[i][estimationXCoordinate];
		}
    }

	tempFactor = (maxTemp - minTemp - 100)/250; //uwaga 100 - sta³a Kowalskiego!!

	ofstream logStream;
	logStream.open("robotVision.log");

    for(int i=0; i<640; i+=2){

		logStream <<  "ttcmatrix[i][estimationXCoordinate]" <<  ttcmatrix[i][estimationXCoordinate] << endl;
		cout << " ttcmatrix[i][estimationXCoordinate]" <<  ttcmatrix[i][estimationXCoordinate] << endl;
        line(plot, Point(i, ttcmatrix[i][estimationXCoordinate]/tempFactor),  Point(i+1, ttcmatrix[i+1][estimationXCoordinate]/tempFactor),  Scalar(0,0,0));
    }
	logStream.close();
	cout << "estimate 9 " <<endl;

    cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);
    imshow("Window", plot); //not needed anymore since the plot is shown in QLabel
	cout << "estimate 10 " <<endl;

    line(ttcMap, Point(0, estimationXCoordinate),  Point(640, estimationXCoordinate),  Scalar(255,0,0)); //red line on ttcMap

    vec.push_back(eflow);
    vec.push_back(dflow);
    vec.push_back(ttcMap);
    vec.push_back(plot);

    return vec;
}

//given two frames, it depicts imprecise relative depth basing on optical flow
void RobotVision::estimateRelativeDepth(Mat frame1, Mat frame2, Mat &pRelDepth){

    Mat gray1, gray2, flow, cflow, ttcmap;

    cvtColor(frame1, gray1, COLOR_BGR2GRAY);
    cvtColor(frame2, gray2, COLOR_BGR2GRAY);

    calcOpticalFlowFarneback(gray1, gray2, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    cvtColor(gray1, cflow, COLOR_GRAY2BGR);
    drawOptFlowMap(flow, cflow, 8, Scalar(0, 255, 0));
    //drawPoorDepth(flow, pRelDepth, ttcmap, 1);

    assert(!cflow.empty()); //debug
    assert(!pRelDepth.empty()); //debug

    cout << "void estimateRelativeDepth()" << endl; //debug
}

void RobotVision::showPoorDepthInRealTime(){
    Mat frame1, frame2, result;
    cvNamedWindow("Camera_Output_D", CV_WINDOW_AUTOSIZE); //Create window

    while(cvWaitKey(10)!=27){

        if(getRobotSpeed()!=0){
            capt >> frame1; // get a new frame from camera
            Sleep(2500); //TODO do sth better...
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
    //todo: this is just a mock. it should take parameters (i.e. results of
    //measurement) and draw a real plot
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

 pair <int, int> RobotVision::findFOE(){
     //todo: this is just a mock... implement methods for real FOE calculation.
     //now it always puts FOE in the center of the image.
    int x, y;
    pair <int, int> result;

    x = this->mesuredAreaWidth/2;
    y = this->mesuredAreaHeight/2;  //todo: take also vertical position into account

    FOE.first = x;
    FOE.second = y;

    result = pair<int, int>(x, y);

    return result;
 }

 void RobotVision::drawFOE(pair <int, int> foe, Mat &frame){
    circle(frame, Point(foe.first, foe.second), 6, Scalar(255, 0, 0));
 }


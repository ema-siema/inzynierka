#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;
using namespace cv;

typedef vector <Point2f> myPoints;
int maxCorners = 150;
int maxTrackbar = 100;
RNG rng(12345);

/**
 * @function goodFeaturesToTrack_Demo.cpp
 * @brief Apply Shi-Tomasi corner detector
 */
void goodFeaturesToTrack_Demo( int, void*, Mat src, string winName, myPoints &corners)
{
  if( maxCorners < 1 ) { maxCorners = 1; }

  /// Parameters for Shi-Tomasi algorithm

  double qualityLevel = 0.01;
  double minDistance = 10;
  int blockSize = 3;
  bool useHarrisDetector = false;
  double k = 0.04;

  Mat copy, frameGray;
  copy = src.clone();
  cvtColor(copy, frameGray, CV_BGR2GRAY);

  /// Apply corner detection
  goodFeaturesToTrack( frameGray,
               corners,
               maxCorners,
               qualityLevel,
               minDistance,
               Mat(),
               blockSize,
               useHarrisDetector,
               k );

  //cout << "** Number of corners detected: " << corners.size() << endl;
  
  /// Draw corners detected
  int r = 4;
  for( int i = 0; i < corners.size(); i++ )
     { circle( copy, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255),
              rng.uniform(0,255)), -1, 8, 0 ); }

  /// Show what you got
  //namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  imshow( winName, copy );
}

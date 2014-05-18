#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

//int maxCorners = 150;

using namespace std;
using namespace cv;

typedef vector <Point2f> myPoints;
static const double PI = 3.14159265358979323846;

void drawFlow(Mat frameC, vector<uchar> status, myPoints corners, myPoints corners2, string winName){
	/* Draw the flow field. */
	for(int i = 0; i < maxCorners; i++)
	{
		/* If Pyramidal Lucas Kanade didn't really find the feature, skip it. */
		if ( status[i] == 0 )
		continue;
		int line_thickness;
		line_thickness = 1;

		/* CV_RGB(red, green, blue) is the red, green, and blue components
		* of the color you want, each out of 255.
		*/
		CvScalar line_color;
		line_color = CV_RGB(255,0,0);

		/* Let's make the flow field look nice with arrows. */
		/* The arrows will be a bit too short for a nice visualization because of the
		high framerate
		* (ie: there's not much motion between the frames). So let's lengthen them
		by a factor of 3.
		*/

		CvPoint p,q;
		p.x = (int) corners[i].x;
		p.y = (int) corners[i].y;
		q.x = (int) corners2[i].x;
		q.y = (int) corners2[i].y;
		double angle;
		double hypotenuse;
		angle = atan2( (double) p.y - q.y, (double) p.x - q.x );
		hypotenuse = sqrt( square(p.y - q.y) + square(p.x - q.x) );

		/* Here we lengthen the arrow by a factor of three. */
        q.x = (int) (p.x -  hypotenuse * cos(angle));
        q.y = (int) (p.y -  hypotenuse * sin(angle));

		/* Now we draw the main line of the arrow. */
		/* "frame2" is the frame to draw on.
		* "p" is the point where the line begins.
		* "q" is the point where the line stops.
		* "CV_AA" means antialiased drawing.
		* "0" means no fractional bits in the center cooridinate or radius.
		*/
		line( frameC, p, q, line_color, line_thickness, CV_AA, 0 );

		/* Now draw the tips of the arrow. I do some scaling so that the
		* tips look proportional to the main line of the arrow.
		*/
        p.x = (int) (q.x + 3 * cos(angle + PI / 4));
        p.y = (int) (q.y + 3 * sin(angle + PI / 4));
		line( frameC, p, q, line_color, line_thickness, CV_AA, 0 );
        p.x = (int) (q.x + 3 * cos(angle - PI / 4));
        p.y = (int) (q.y + 3 * sin(angle - PI / 4));
		line( frameC, p, q, line_color, line_thickness, CV_AA, 0 );
	}
 	imshow( winName, frameC );
}

# include "balls.hpp"
# include <stdio.h> 
# include <vector>
# include <map>
// openCV libs
# include "opencv2/highgui/highgui.hpp"
# include "opencv2/imgproc/imgproc.hpp"
# include "opencv2/opencv.hpp"
# include "opencv2/core/core.hpp"

# include <sys/time.h>

# include <math.h>

using namespace cv;
using namespace std;

BallFinder::BallFinder()
{
    ballPose.x = 0;
	ballPose.y = 0;
	ballPose.z = 0;
	ballPose.th = 0;
    ballPose.id = 0;
    ballPose.valid = false;
    //HSV Values
    //Orange
    orangeHSV.HSV_lower[0] = 0;
    orangeHSV.HSV_lower[1] = 140;
    orangeHSV.HSV_lower[2] = 90;

    orangeHSV.HSV_upper[0] = 28;
    orangeHSV.HSV_upper[1] = 255;
    orangeHSV.HSV_upper[2] = 255;
    //White
    whiteHSV.HSV_lower[0] = 30;
    whiteHSV.HSV_lower[1] = 20;
    whiteHSV.HSV_lower[2] = 50;

    whiteHSV.HSV_upper[0] = 180;
    whiteHSV.HSV_upper[1] = 80;
    whiteHSV.HSV_upper[2] = 255;
}

BallFinder::~BallFinder(){

};

pose_t BallFinder::find_ball(cv::Mat frame, bool show_image, bool red_or_white,bool debug) {
    Mat cropped;
    Mat blurred;
    Mat mask;
    Mat mask_eroded;
    Mat mask_dilated;
    Mat HSV;

    //Crop the top 50%
    cropped = imageReducer(frame,60);
    if (debug) {
        imshow("cropped", cropped);
        waitKey(0);
    }
    
    //Blurred
    GaussianBlur(cropped,blurred,Size(11, 11),0);

    int width; int height;
    height = cropped.size[0];
    width = cropped.size[1];

    cvtColor(blurred, HSV, COLOR_BGR2HSV);

    if (red_or_white == RED) {
        inRange(HSV, Scalar (orangeHSV.HSV_lower[0],orangeHSV.HSV_lower[1],orangeHSV.HSV_lower[2]),
    Scalar (orangeHSV.HSV_upper[0],orangeHSV.HSV_upper[1],orangeHSV.HSV_upper[2]),mask);
    }
    else if (red_or_white == WHITE){
        inRange(HSV, Scalar (whiteHSV.HSV_lower[0],whiteHSV.HSV_lower[1],whiteHSV.HSV_lower[2]),
    Scalar (whiteHSV.HSV_upper[0],whiteHSV.HSV_upper[1],whiteHSV.HSV_upper[2]),mask);
    }

    if (debug) {
        imshow("mask", mask);
        waitKey(0);
    }
    
    // Create a structuring element (SE)
    int morph_size = 2;
    Mat element = getStructuringElement(MORPH_RECT, Size(11,11));
    
    Mat erod, dill;

    erode(mask,mask_eroded,element,Point(-1, -1), 2);

    if (debug){
        imshow("Eroded", mask_eroded);
        waitKey(0);
    }
    

    dilate(mask_eroded,mask_dilated,element,Point(-1, -1), 2);
    
    if (debug) {
        imshow("Dilated", mask_dilated);
        waitKey(0);
    }
    
    vector<vector<Point>> contours;
    findContours(mask_dilated,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    //vector<Vec3f> contours;
    //HoughCircles(mask_dilated, contours, HOUGH_GRADIENT, 1, 18, 180, 18, 10, 25);
    // Approximate contours to polygons + get bounding circles
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Point2f>centers( contours.size() );
    vector<float>radius( contours.size() );
    
    int idx = -1, max_area=0;
    for( size_t i = 0; i < contours.size(); i++ ){
        approxPolyDP( contours[i], contours_poly[i], 3, true );
        minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
        int area = (int)contourArea(contours_poly[i]);     
        if (area > max_area){
            idx = (int)i;
            max_area = area;
        }
    }

  
    if (idx>-1){
        cout << "Ball detected!" << endl;
        circle( cropped, centers[idx], (int)radius[idx], Scalar(0,255,0), 2 );
        circle( cropped, centers[idx], 3, Scalar(255,0,0), -1 );
    }

    if(debug) {
        imshow("Ball", frame);

        waitKey(0); // Wait for any keystroke in the window

        destroyAllWindows(); //destroy all opened windows
    }

    return ballPose;
}

 /* Point_<int> v0,v1,h0,h1;
    int offset_ball = 0;
    h0 = Point(0,480 + offset_ball); 
    h1 = Point(1280, 480 + offset_ball);
    v0 = Point(640 + offset_ball,0);
    v1 = Point(640 + offset_ball, 960);

    // Point in the image where we need to detect the ball in order to grab it correctly
    Point_<int> pt_ball_detection = Point(640 + offset_ball, 210 + offset_ball);
    circle(frame, pt_ball_detection, 10, Scalar(0,0,255),-1); 
    line(frame, v0, v1, Scalar(0,0,255), 2);
    line(frame, h0, h1, Scalar(0,0,255), 2);*/


/*
    // Find Largest Contour
    Rect brect;
    int max_diameter = 0;
    int max_idx = 0;
    for(unsigned int j = 0; j< contours.size(); j++)
    {
        drawContours(mask_dilated, contours, j, Scalar(200), 1, 8, 0, Point() );
        brect = boundingRect(contours.at(j));
        if (brect.height > max_diameter && brect.y < 350 && brect.y > 50)
        {
            max_diameter = brect.height;
            max_idx = j;
        }
    }*/

Mat BallFinder::imageReducer(Mat image, int percentage) {
	Mat cropped_image;

    int width; int height;
    height = image.size[0];
    width = image.size[1];

    int newHeight;
    newHeight = (height/100)*percentage;

    cropped_image = image(Range(newHeight,height),Range(0,width));

    return cropped_image;
}

#include "balls.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <string>

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
    pose_t ballPose;
    BallFinder ball_finder = BallFinder();

    Mat image = imread("/home/hcgl/Desktop/orange_balls/orange_pics/1m.jpg");

    ballPose = ball_finder.find_ball(image,true, RED);
    
    cout << " x: " << ballPose.x << " y: " << ballPose.y << " z: " << ballPose.z << endl;

   /* namedWindow("Aruco");
    imshow("Aruco", image);

    waitKey(0); // Wait for any keystroke in the window

    destroyAllWindows(); //destroy all opened windows*/
}
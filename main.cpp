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

    //Single image:

    //Mat image = imread("/home/hcgl/Desktop/ball_detection/white_pics/60.jpg");
    //namedWindow("Ball");
    //imshow("Ball", image);
    //cout << " x: " << ballPose.x << " y: " << ballPose.y << " z: " << ballPose.z << endl;
    // waitKey(0); // Wait for any keystroke in the window

    //looping through all:
    String folderpath = "/home/hcgl/Desktop/ball_detection/white_pics/*.jpg";
    vector<String> filenames;
    cv::glob(folderpath, filenames);

    for (size_t i=0; i<filenames.size(); i++)
    {
        Mat image = imread(filenames[i]);
        ballPose = ball_finder.find_ball(image,true, WHITE, false);

        imshow("Ball", image);
        waitKey(0); // Wait for any keystroke in the window
    }
    
    destroyAllWindows(); //destroy all opened windows*/
}
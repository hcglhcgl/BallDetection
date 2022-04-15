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
    pose_t stubPose;
    BallFinder ball_finder = BallFinder();

    // Single image:

    /*
    // FINDING BALL
    ballPose = ball_finder.find_ball(image,true, RED, false);
    namedWindow("Ball");
    imshow("Ball", image);
    cout << " x: " << ballPose.x << " y: " << ballPose.y << " z: " << ballPose.z << endl;
    //

    //FINDING TREESTUB
    Mat image = imread("/home/hcgl/Desktop/ball_detection/photos/pic_left_1.jpg");
    stubPose = ball_finder.trunkFinder(image,false, true);
    namedWindow("Trunk");
    imshow("Trunk", image);

    if (stubPose.valid) {
        cout << " x: " << stubPose.x << " y: " << stubPose.y << " z: " << stubPose.z << endl;
    }

    waitKey(0);
    */

    // Looping through all files in a folder:

    /*
    String folderpath = "/home/hcgl/Desktop/ball_detection/photos/*.jpg";
    vector<String> filenames;
    cv::glob(folderpath, filenames);

    for (size_t i=0; i<filenames.size(); i++)
    {
        Mat image = imread(filenames[i]);
        ballPose = ball_finder.find_ball(image,true, RED, true);

        if(ballPose.valid) {
            cout << " x: " << ballPose.x << " y: " << ballPose.y << " z: " << ballPose.z << endl;
        }

        imshow("Ball", image);
        waitKey(0); // Wait for any keystroke in the window
    } 
    */

   // Loading a video 
   ///*
    VideoCapture cap("/home/hcgl/Desktop/ball_detection/videos/video.h264"); 
   
    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    while(1){

        Mat frame;
        // Capture frame-by-frame
        cap >> frame;
    
        // If the frame is empty, break immediately
        if (frame.empty())
        break;

        //ballPose = ball_finder.find_ball(frame,true, RED, false);
        /*
        ballPose = ball_finder.treeID(frame,false, RED, false);

        if(ballPose.valid) {
            cout << " x: " << ballPose.x << " y: " << ballPose.y << " z: " << ballPose.z << endl;
            if (ballPose.id == WHITE){
                cout << "WHITE TREE" << endl;
            }
            else if (ballPose.id == RED) {
                cout << "RED TREE" << endl;
            }
            else {
                cout << "UNABLE TO ID TREE" << endl;
            }
        } */

        stubPose = ball_finder.trunkFinder(frame,false, false);
        namedWindow("Trunk");
        imshow("Trunk", frame);

        if (stubPose.valid) {
        cout << " x: " << stubPose.x << " y: " << stubPose.y << " z: " << stubPose.z << endl;
        }

        // Press  ESC on keyboard to exit
        char c=(char)waitKey(25);
        if(c==27)
        break;
    }
 
    // When everything done, release the video capture object
    cap.release();
    ///*

    destroyAllWindows(); //destroy all opened windows*/

    return 0;
}
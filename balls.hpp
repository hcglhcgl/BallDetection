#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/core.hpp"

#define RED 0
#define WHITE 1

using namespace cv;
using namespace std;

struct pose_t
{
    bool valid;
    double x;
    double y;
    double z;
    double th;
    long num_pose;
    int id;
};

struct HSV 
{
    int HSV_lower[3];
    int HSV_upper[3];
};

class BallFinder
{
    public:
        BallFinder();
        ~BallFinder();
        pose_t find_ball(cv::Mat frame, bool show_image, bool red_or_white, bool debug);
        Mat imageReducer(Mat image, int percentage);
    private:
        pose_t ballPose;
        Mat cameraMatrix;
	    Mat distCoeffs;
        HSV orangeHSV;
        HSV whiteHSV;
};



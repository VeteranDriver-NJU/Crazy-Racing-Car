#include <cstdlib>
#include <iostream>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "GPIOlib.h"
#include "Camera.h"

#define PI 3.1415926

//Uncomment this line at run-time to skip GUI rendering
//#define _DEBUG

using namespace cv;
using namespace std;
using namespace GPIO;

const string CAM_PATH="/dev/video0";
const string MAIN_WINDOW_NAME="Processed Image";
const string CANNY_WINDOW_NAME="Canny";

const int CANNY_LOWER_BOUND=30;
const int CANNY_UPPER_BOUND=90;
const int HOUGH_THRESHOLD=50;

const int GOD = 300;

int main()
{
    GPIO::init();
    VideoCapture capture(CAM_PATH);
    //If this fails, try to open as a video camera, through the use of an integer param
    if (!capture.isOpened())
    {
        capture.open(atoi(CAM_PATH.c_str()));
    }
    
    double dWidth=capture.get(CV_CAP_PROP_FRAME_WIDTH);			//the width of frames of the video
    double dHeight=capture.get(CV_CAP_PROP_FRAME_HEIGHT);		//the height of frames of the video
    clog<<"Frame Size: "<<dWidth<<"x"<<dHeight<<endl;
    
    Mat image;
    int i = 1;
    int doge = 0;
  
    int should_turn_left = 0;
    while(true)
    {
        controlLeft(1,10);
        controlRight(1,10);
        doge++;
        cout << "doge: " << doge << endl;
        if(i == 2){
            if(should_turn_left > 0){
                clog << "turn left" << endl;
                turnTo(-6);
            }
            if(should_turn_left < 0){
                clog << "turn right" << endl;
                turnTo(8);
            }
            i = 0;
        }
        should_turn_left = 0;
        i++;
//        capture>>image;
//        camera.update();
//        if(image.empty())
//            break;

//        _img = camera.get_img();
//        imshow("original", _img);
//
//        _img = camera.get_garyscale_img();
//        imshow("grayscale", _img);
//
//        _img = camera.get_sobel_x_img();
//        imshow("sobel_x", _img);

        // 加入灰度和二值化
        camera.update();
        image = camera.get_mag_thresh_img();
        imshow("grad_thresh", _img);

        int key = waitKey(10);
        if (key == 27) {
            cout << "ecs break" << endl;
            break;
        }
        
        Rect roi(0, image.rows / 3, image.cols / 2, image.rows / 3);
        Mat imgROI = image(roi);
        
        //Canny algorithm
        Mat contours;
        //blur(imgROI,imgROI,Size(30,30));
        Canny(imgROI, contours, CANNY_LOWER_BOUND, CANNY_UPPER_BOUND);
        
        //    waitKey();
        //    return 0;
        vector<Vec4i> lines;
        //HoughLinesP(contours,lines,1, PI/180, 100, 20, 50);
        HoughLinesP(contours, lines, 1, PI / 180, HOUGH_THRESHOLD, 20, 5);
        Mat result(imgROI.size(), CV_8U, Scalar(255));
        imgROI.copyTo(result);
        clog << lines.size() << endl;
        GOD++;
        
        //Draw the lines and judge the slope
        int color = 50;
        
        for (vector<Vec4i>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
            line(result, Point((*it)[0], (*it)[1]), Point((*it)[2], (*it)[3]), Scalar(color, color, 255), 20, CV_AA);
            float slope = ((float) (*it)[3] - (*it)[1])/((*it)[2] - (*it)[0]);
            clog << "slope" << slope << endl;
            if(slope <= 2 && slope >= 0.3){
                should_turn_left++;
            }
    
            if(slope >= -2 && slope <= -0.3){
                should_turn_left--;
            }

            // 左盒子
            if(slope >= 10 && slope <= 15) {
                turnTo(-22);
            }

            int degree = 20;

            int offset = (slope - 20)/4;

            clog << "offset: " <<  offset << endl;

            // 向左，大盒子
            if(slope >= 4 && slope <= 60) {
                turnTo(degree + offset);
            }
            
            // 向右, 小盒子
            if(slope >= 4 && slope <= 60) {
                turnTo(degree - offset);
            }

            // 修偏角
            if(slope > 60) {
                turnTo(-6);
            }

            if(slope < -4) {
                turnTo(4);
            }

            color += 50;
            color %= 256;

        }

        stringstream overlayedText;
        overlayedText<<"Lines: "<<lines.size();
        putText(result,overlayedText.str(),Point(10,result.rows-10),2,0.8,Scalar(0,0,255),0);
        imshow(MAIN_WINDOW_NAME,result);

        
        lines.clear();
        waitKey(1);
    }
    return 0;
}

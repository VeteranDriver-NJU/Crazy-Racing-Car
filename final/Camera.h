//
// Created by aquafits on 18-10-18.
//

#ifndef SPINNING_CAR_CAMERA_H
#define SPINNING_CAR_CAMERA_H

#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

#include "Properties.h"
#include "Util.h"

using namespace std;
using namespace cv;

class Camera {
private:
    string mode;
    string ip_camera_address = "";
    VideoCapture capture = VideoCapture(0);
    Mat img = Mat();

public:
    Camera(const string &mode, const string &ip_camera_address) : mode(mode), ip_camera_address(ip_camera_address) {
        if (mode != "ip_camera") {
            cout << "init with mode \"ip_camera\" to link to ip camera" << endl;
            return;
        }

        capture.open(ip_camera_address);
    }

    Camera() {}


    ~Camera(){
        capture.release();
    }

    void relocate(string path){
        img = imread(path);
        imshow("relocate file", img);
    }

    void update(){
        capture >> img;
    }


    Mat get_img(){
        return img;
    }

    Mat get_garyscale_img(){
        return grayscale(img);
    }

    Mat get_sobel_x_img(){
        return sobel_x_thresh(img);
    }

    Mat get_mag_thresh_img(){
        return grad_thresh(img);
    }
};

#endif //SPINNING_CAR_CAMERA_H

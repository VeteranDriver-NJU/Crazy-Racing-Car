//
// Created by aquafits on 18-10-18.
//

#ifndef SPINNING_CAR_UTIL_H
#define SPINNING_CAR_UTIL_H

#include <iostream>

#include <opencv2/opencv.hpp>
#include "Properties.h"

using namespace std;
using namespace cv;

Mat grayscale(Mat &img){
    Mat gray;
    cvtColor(img, gray, CV_RGB2GRAY);
    return gray;
}

Mat gaussian_blur(Mat &img, Size kernel_size){
    Mat gaussion;
    GaussianBlur(img, gaussion, kernel_size, 0);
    return gaussion;
}

Mat sobel_x_thresh(Mat &img, int sobel_size = 3){
    Mat gaussian = gaussian_blur(img,Size(5,5));
    Mat gray = grayscale(gaussian);

    //Take only Sobel x
    Mat sobel_x, abs_sobel_x;
    Sobel(gray, sobel_x, CV_64F, 1, 0, sobel_size);
    //Calculate the absolute value of the x derivative
    convertScaleAbs(sobel_x, abs_sobel_x);
    Mat sobel_x_binary = abs_sobel_x.clone();

    for(int k = 0; k<abs_sobel_x.rows;k++){
        for(int kk = 0; kk<abs_sobel_x.cols;kk++){
            //Convert the absolute value image to 8-bit
            int n = abs_sobel_x.at<uchar >(k, kk);
            abs_sobel_x.at<uchar >(k, kk) = (uchar)n;
        }
    }
    return sobel_x_binary;
}

Mat grad_thresh(Mat &img, int sobel_size = 3){
    Mat gaussian = gaussian_blur(img,Size(5,5));
    Mat gray = grayscale(gaussian);

    //Take both Sobel x and y gradients
    Mat sobel_x;
    Sobel(gray, sobel_x, CV_64F, 1, 0, sobel_size);
    Mat sobel_y;
    Sobel(gray, sobel_y, CV_64F, 0, 1, sobel_size);
    Mat grad = sobel_x.clone();

    //Calculate the gradient magnitude
    convertScaleAbs( sobel_x, sobel_x );
    convertScaleAbs( sobel_y, sobel_y );
    addWeighted( sobel_x, 0.5, sobel_y, 0.5, 0, grad );
    Mat grad_binary = grad.clone();

    for(int k = 0; k<grad.rows;k++){
        for(int kk = 0; kk<grad.cols;kk++){
            //Rescale to 8 bit
            int n = grad.at<uchar >(k, kk);
            grad.at<uchar >(k, kk) = (uchar)n;
        }
    }
    return grad_binary;

}

#endif //SPINNING_CAR_UTIL_H

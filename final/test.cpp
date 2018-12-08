//
// Created by py on 2018/10/20.
// test.cpp extends from the py's version 0, adding brother Qiu's detection
#include "Util.h"
#include "Camera.h"

const string IMG_PATH = "/Users/py/GitHub/spinning-car/test_files/2.jpg";
void test_img_process() {
    Camera camera;
    Mat img;

    for(;;) {
        camera.relocate(IMG_PATH);
        img = camera.get_img();
        imshow("Original", img);
        img = camera.get_garyscale_img();
        imshow("Gray_Scale", img);
        img = camera.get_sobel_x_img();
        imshow("Sobel_x", img);
//        img = camera.get_mag_thresh_img();
//        imshow("Final", img);

        int key = waitKey(10);
        if (key == 27) {
            cout << "ecs break" << endl;
            break;
        }
    }
}

int main() {
    test_img_process();
}
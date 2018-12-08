#include <iostream>
#include "Camera.h"

int main() {
    Camera camera;
//    Camera camera = Camera("ip_camera", "http://admin:123@192.168.0.103:8081");

    Mat _img;
    while (true){
        camera.update();
//        camera.relocate("/home/aquafits/Documents/Repos/spinning-car/test_files/2.jpg");

        _img = camera.get_img();
        imshow("original", _img);

        _img = camera.get_garyscale_img();
        imshow("grayscale", _img);

        _img = camera.get_sobel_x_img();
        imshow("sobel_x", _img);

        _img = camera.get_mag_thresh_img();
        imshow("grad_thresh", _img);

        int key = waitKey(10);
        if (key == 27) {
            cout << "ecs break" << endl;
            break;
        }
    }
    return 0;
}
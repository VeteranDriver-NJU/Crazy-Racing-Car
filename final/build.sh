sudo g++ final_test.cpp -o stable `pkg-config --cflags --libs opencv` -L. -lwiringPi -lGPIO -lpthread
sudo ./stable

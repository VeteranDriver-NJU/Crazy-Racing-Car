sudo g++ pre.cpp -o test `pkg-config --cflags --libs opencv` -L. -lwiringPi -lGPIO -lpthread
sudo ./test

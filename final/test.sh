sudo g++ pre.cpp -o pre `pkg-config --cflags --libs opencv` -L. -lwiringPi -lGPIO -lpthread
sudo ./pre

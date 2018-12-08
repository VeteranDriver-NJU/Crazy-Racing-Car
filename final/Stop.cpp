//
// Created by py on 2018/10/17.
//

#include <iostream>
#include "GPIOlib.h"
using namespace std;
using namespace GPIO;

int main() {
    init();
    stopLeft();
    stopRight();
    return 0;
}

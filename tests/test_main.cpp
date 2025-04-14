#include <iostream>

// include library
#include "sensorFunctions.h"

// include tests
#include "lv_sensors_test.hpp"

int main() {
    std::cout << "This is the test file" << std::endl;

    LV_TEST lv_test;
    lv_test.currentTest();

    return 0;
}
#include <iostream>

// include library
#include "sensorFunctions.h"

// include tests
#include "lv_sensors_test.hpp"
#include "mppt_test.hpp"
#include "mcu_test.hpp"

int main() {
    // LV_TEST lv_test;
    // lv_test.currentTest();
    
    MPPT_Test mppt_test;

    mppt_test.test();
    LV_TEST lv_test;
    lv_test.currentTest();
    lv_test.voltageTest();
    lv_test.tempTest();
    lv_test.testGPS();

    MCU_TEST mcu_test;
    mcu_test.motorDataTest();
    mcu_test.throttleDataTest();

    return 0;
}

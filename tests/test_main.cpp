#include <iostream>

// include library
#include "sensorFunctions.h"

// include tests
#include "lv_sensors_test.hpp"
#include "mppt_test.hpp"
#include "mcu_test.hpp"

#define TEST_LV
#define TEST_MPPT

int main() {
#ifdef TEST_LV
    LV_TEST lv_test;
    lv_test.currentTest();
    lv_test.voltageTest();
    lv_test.tempTest();
    lv_test.testGPS();
#endif
    
#ifdef TEST_MPPT
    MPPT_Test mppt_test;
    mppt_test.powerTest();
    mppt_test.statusTest();
#endif
    
    MCU_TEST mcu_test;
    mcu_test.motorDataTest();

    return 0;
}

#include <iostream>

// include library
#include "sensorFunctions.h"

// include tests
#include "lv_sensors_test.hpp"
#include "mppt_test.hpp"

#define TEST_MPPT
#define TEST_LV

int main() {
#ifdef TEST_LV
    LV_TEST lv_test;
    lv_test.currentTest();
#endif
    
#ifdef TEST_MPPT
    MPPT_Test mppt_test;
    mppt_test.powerTest();
#endif
    
    return 0;
}

#ifndef __MPPT_H__
#define __MPPT_H__

#include <iostream> // TODO make sure this compiles in arduino

const float voltageScaleFactor = 0.01; 
const float currentScaleFactor = 0.0005;

// Create an instance of this class for each array
class MPPT {
    private: 
        int inVoltage;
        int outVoltage;
        int inCurrent;
        int outCurrent;

    public:
        std::string getModeName(uint8_t modeNum);
};


#endif

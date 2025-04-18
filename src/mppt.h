#ifndef __MPPT_H__
#define __MPPT_H__

#include <iostream> // TODO make sure this compiles in arduino
#include <cstdint>

#include "can.h"
#include "canFloat.h"

const float voltageScaleFactor = 0.01; 
const float currentScaleFactor = 0.0005;

typedef struct powerMeasurements {
    float inVoltage;
    float outVoltage;
    float inCurrent;
    float outCurrent;
} powerMeasurements;

typedef struct mpptStatus {
    uint8_t mode;
    uint8_t fault;
    bool enabled;
    int ambientTemp;
    int heatsinkTemp;
} mpptStatus;

// Create an instance of this class for each array
class MPPT {
    private: 
        int16_t combineBytes(uint8_t high, uint8_t low);

    public:
        // parsing
        powerMeasurements parsePowerMeasurements(uint8_t data[], bool debug);
        mpptStatus parseMPPTStatus(uint8_t data[], bool debug);

        // getters
        std::string getModeName(uint8_t modeNum);
        
};


#endif

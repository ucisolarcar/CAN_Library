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
    int mode;
    int fault;
    bool enabled;
    int ambientTemp;
    int heatsinkTemp;
} mpptStatus;

// Create an instance of this class for each array
class MPPT {
    private: 
        int16_t combineBytes(uint8_t high, uint8_t low);
        std::string modeStrs[7] = {"Constant Input Voltage", 
                                "Constant Input Current",
                                "Minimum Input Current",
                                "Constant Output Voltage",
                                "Constant Output Current",
                                "Temperature Derating", 
                                "Fault"};

        std::string faultStrs[8] = {"OK No Error",
                                   "Configuration Error",
                                   "Input Over Voltage",
                                   "Output Over Voltage",
                                   "Output Over Current",
                                   "Input Over Current",
                                   "Input Under Current",
                                   "Phase Over Current"};
    public:
        // parsing
        powerMeasurements parsePowerMeasurements(uint8_t data[]);
        mpptStatus parseMPPTStatus(uint8_t data[]);

        // getters
        std::string getModeName(int modeNum);
        std::string getFaultName(int faultNum);
};


#endif

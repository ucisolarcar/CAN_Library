#ifndef __MCU_H__
#define __MCU_H__

#include <iostream> // TODO make sure this compiles in arduino
#include <cstdint>

#include "can.h"
#include "canFloat.h"
#include <vector>

using namespace std;

typedef struct ControllerStatus
{
    uint8_t statusFeedback;
    uint8_t statusCmd;
} ControllerStatus;

typedef struct MotorData
{
    float rpm;
    float mcuCurrent;
    float mcuVoltage;
    bool mcuFaults[16];
} MotorData;

typedef struct ThrottleData
{
    uint8_t mcuThrottle;
    uint8_t mcuTemp;
    uint8_t motorTemp;
    bool swStatus[8];
    ControllerStatus controllerStatus;
} ThrottleData;

class MCU {
    private:
        //ControllerStatus parseControllerStatus(uint8_t data[], bool debug);
        //MCUSwitchStatus parseSWSignals(uint8_t data[], bool debug);
    public:
        //constructor:
        MCU();

        // Message 1 related functions:
        MotorData parseMotorData(uint8_t data[], bool debug);

        // Message 2 related functions:
        ThrottleData parseThrottleData(uint8_t data[], bool debug);        
};

#endif
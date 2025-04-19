#ifndef __MCU_H__
#define __MCU_H__

#include <iostream> // TODO make sure this compiles in arduino
#include <cstdint>

#include "can.h"
#include "canFloat.h"
#include <vector>

using namespace std;

typedef struct MCUSwitchStatus
{
    bool boostSW;
    bool footSW;
    bool forwardSW;
    bool backwardSW;
    bool brake12V;
    bool hallC;
    bool hallB;
    bool hallA;
} MCUSwitchStatus;

typedef struct ControllerStatus
{
    uint8_t statusFeedback;
    uint8_t statusCmd;
} ControllerStatus;

class MCU {
    private:

    public:
        //constructor:
        MCU();

        // Message 1 related functions:
        float parseRPM(uint8_t data[], bool debug);
        float parseMCUCurrent(uint8_t data[], bool debug);
        float parseMCUVoltage(uint8_t data[], bool debug);
        // Return an array of 16 booleans of faults
        bool* parseFaults(uint8_t data[], bool debug);

        // Message 2 related functions:
        uint8_t parseMCUThrottle(uint8_t data[], bool debug);
        uint8_t parseMCUTemp(uint8_t data[], bool debug);
        uint8_t parseMotorTemp(uint8_t data[], bool debug);
        ControllerStatus parseControllerStatus(uint8_t data[], bool debug);
        MCUSwitchStatus parseSWSignals(uint8_t data[], bool debug);
};

#endif
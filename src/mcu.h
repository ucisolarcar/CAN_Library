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
    uint16_t rpm;
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
        string faultStrs[16] = {"Idenfitication", "Over Voltage", "Low Voltage", "reserved", "Stall", 
        "Internal Volts Fault", "Over Temperature", "Throttle Error At Power up", "reserved", "Internal Reset",
        "Hall Throttle Is Open or Short Circuit", "Angle Sensor Error"};

        string swStatusStrs[8] = {"Hall A", "Hall B", "Hall C", "12V Brake Switch", "Backward Switch", "Forward Switch", "Foot Switch", "Boost Switch"};

        string feedbackStrs[4] = {"Stationary", "Forward", "Backward", "Reserved"};
        string commandStrs[4] = {"Neutral", "Forward", "Backward", "Reserved"};

    public:
        //constructor:
        MCU();

        // Message 1 related functions:
        MotorData parseMotorData(uint8_t data[]);

        // Message 2 related functions:
        ThrottleData parseThrottleData(uint8_t data[]);        

        // getter functions for message strings
        std::string getFaultStr(int faultNum);
        std::string getSwStatusStr(int statusNum);
        std::string getFeedbackStr(int feedbackNum);
        std::string getCommandStr(int commmandNum);
};

#endif

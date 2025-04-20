#include "mcu.h"

using namespace std;

MCU::MCU()
{

}

/*
Parse message 1 (CAN ID: 0x0CF11E05)
- get RPM
- get current
- get voltage
- get faults

and return the corresponding MotorData
*/ 
MotorData parseMotorData(uint8_t data[], bool debug)
{
    cout << "parsing motor data\n";
    uint16_t rpm = (data[1] * 256) + data[0];
    uint16_t current = (data[3] * 256) + data[2];
    uint16_t voltage = (data[5] * 256) + data[4];

     // Now create that MotorData struct
     MotorData resultData;
     resultData.rpm = rpm;
     resultData.mcuCurrent = current;
     resultData.mcuVoltage = voltage;
     
    // create an array of bools for the mcuFaults
    uint8_t mask = 0b1;

    // Find out if the bit is flagged (1) in the message and record that state in the array
    // NEED TO TEST
    int index = 6;
    for (int i = 0; i < 16; i++)
    {
        resultData.mcuFaults[i] = (bool) (data[index] & mask);
        mask << 1;
        index = i > 7 ? 7 : 6;
    }

    return resultData;
}

/*
Parse message 2 (CAN ID: 0x0CF11F05)
- get throttle
- get mcuTemp
- get motorTemp
- get swStatus
- get controllerStatus

and return the corresponding MotorData
*/ 
ThrottleData parseThrottleData(uint8_t data[], bool debug)
{
    ThrottleData resultData;

    resultData.mcuThrottle = data[0];
    resultData.mcuTemp = data[1];
    resultData.motorTemp = data[2];

    resultData.controllerStatus.statusFeedback = data[4] & 0b00001100;
    resultData.controllerStatus.statusCmd = data[4] & 0b00000011;

    uint8_t mask = 0b1;
    for(int i = 0; i < 8; i++)
    {
        resultData.swStatus[i] = data[5] & mask;
        mask << 1;
    }

    return resultData;
}
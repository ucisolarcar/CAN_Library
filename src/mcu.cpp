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
MotorData MCU::parseMotorData(uint8_t data[])
{
    uint16_t rpm = (data[1] * 256) + data[0];
    float current = ((data[3] * 256) + (data[2])) / 10;
    float voltage = ((data[5] * 256) + data[4]) / 10;

     // Now create that MotorData struct
     MotorData resultData;
     resultData.rpm = rpm;
     resultData.mcuCurrent = current;
     resultData.mcuVoltage = voltage;
     
    // create an array of bools for the mcuFaults
    int mask = 0b1;

    // Find out if the bit is flagged (1) in the message and record that state in the array
    // NEED TO TEST
    //int index = 6;
    for (int i = 0; i < 16; i++)
    {
        int index = i < 8 ? 6 : 7;
        resultData.mcuFaults[i] = (data[index] & mask) != 0;

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
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
ThrottleData MCU::parseThrottleData(uint8_t data[])
{
    ThrottleData resultData;

    resultData.mcuThrottle = data[0];
    resultData.mcuTemp = data[1] - 40;
    resultData.motorTemp = data[2] - 30;

    resultData.controllerStatus.statusFeedback = (data[4] & 0b00001100) >> 2;
    resultData.controllerStatus.statusCmd = data[4] & 0b00000011;

    uint8_t mask = 0b1;
    for(int i = 0; i < 8; i++)
    {
        resultData.swStatus[i] = data[5] & mask;
        mask = mask << 1;
    }

    return resultData;
}

std::string MCU::getFaultStr(int faultNum) {
    return faultStrs[faultNum];
}

std::string MCU::getSwStatusStr(int statusNum) {
    return swStatusStrs[statusNum];
}
std::string MCU::getFeedbackStr(int feedbackNum) {
    return feedbackStrs[feedbackNum];
}
std::string MCU::getCommandStr(int commmandNum) {
    return commandStrs[commmandNum];
}

#ifndef __MCU_H__
#define __MCU_H__

#include <iostream> // TODO make sure this compiles in arduino
#include <cstdint>

#include "can.h"
#include "canFloat.h"

/* 
    3 messages that will be sent by BMS. 3 functions to parse each of the messages:
    -   0x300: packInfo
    -   0x301: tempInfo
    -   0x302: faultInfo
*/

const int tempFactor = 1;
const float currentFactor = 0.1;
const float voltageFactor = 0.1;
const float packFactor = 0.1;

// 0x300
typedef struct packInfo {
    float packVoltage;
    float packCurrent;
    float packSOC;
    float packPower;
} packInfo;

// 0x301
typedef struct tempInfo {
    int avgTemp;
    int internalTemp;
    int highTemp;
    int highTempID;     // returns the ID of the thermistor detecting the highest temp reading
} tempInfo;

typedef struct faultInfo {

} faultInfo;

#endif
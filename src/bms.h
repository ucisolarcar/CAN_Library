#ifndef __MCU_H__
#define __MCU_H__

#include <iostream> // TODO make sure this compiles in arduino
#include <cstdint>

#include "can.h"
#include "canFloat.h"

using namespace std;

/* 
    3 messages that will be sent by BMS. 3 functions to parse each of the messages:
    -   0x300: packInfo
    -   0x301: tempInfo
    -   0x302: faultInfo
*/

// In order to normalize and faciliate the correct truncation of the float
// these "factors" will be used. Ensures that we aren't getting extra precision
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
    bool currLimitStatus[16];
    bool dtcFlags1[16];
    bool dtcFlags2[16];
    uint8_t prechargeState;
} faultInfo;

class BMS {
    private:
        // Strings that correspond with the fault messages:

    public:
        // constructor:
        BMS();

        packInfo parsePackInfo(uint8_t data[]);

        tempInfo parseTempInfo(uint8_t data[]);

        faultInfo parseFaults(uint8_t data[]);

        // getter functions for message strings:
        string getCurrLimitStr(int currLimitNum);
        string getDtcFlag1Str(int flag1);
        string getDtcFlag2Str(int flag2);
        string getPrechargeStr(int state);
};

#endif
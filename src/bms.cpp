#include "bms.h"

using namespace std;

BMS::BMS()
{

}

int16_t BMS::combineBytes(uint8_t high, uint8_t low) {
    return static_cast<int16_t>((high << 8) | low);
}


packInfo BMS::parsePackInfo(uint8_t data[])
{
    packInfo output;

    output.packCurrent = (float)combineBytes(data[0], data[1]) * currentFactor;
    output.packVoltage = (float)combineBytes(data[2], data[3]) * voltageFactor;  
    output.packSOC = (float)combineBytes(data[4], data[5]) * socFactor;  // in percent
    output.packPower = (float)combineBytes(data[6], data[7]) * packFactor;

    return output;
}

tempInfo BMS::parseTempInfo(uint8_t data[])
{
    tempInfo output;

    output.avgTemp = (uint8_t) data[0]; //I am a little worried that 0xFF will be a negative number
    output.internalTemp = (uint8_t) data[2];
    output.highTemp = (uint8_t) data[4];
    output.highTempID = (uint8_t) data[6];

    return output;
}

faultInfo BMS::parseFaults(uint8_t data[])
{
    faultInfo output;
    int mask = 0b1;

    // setting flags for current limit status
    for (int i = 0; i < 16; i++)
    {
        int index = i < 8 ? 0 : 1;
        output.currLimitStatus[i] = (bool) ((data[index] & mask) != 0);

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
    }

    mask = 0b1;
    // setting flags for DTC#1:
    for (int i = 0; i < 16; i++)
    {
        int index = i < 8 ? 2 : 3;
        output.dtcFlags1[i] = (bool) ((data[index] & mask) != 0);

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
    }

    mask = 0b1;
    // setting flags for DTC#2:
    for (int i = 0; i < 16; i++)
    {
        int index = i < 8 ? 4 : 5;
        output.dtcFlags2[i] = (bool) ((data[index] & mask) != 0);

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
    }

    output.prechargeState = (uint8_t) data[6];

    return output;
}

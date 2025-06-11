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
        int index = i < 8 ? 1 : 0;
        output.currLimitStatus[i] = (bool) ((data[index] & mask) != 0);

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
    }

    mask = 0b1;
    // setting flags for DTC#1:
    for (int i = 0; i < 16; i++)
    {
        int index = i < 8 ? 3 : 2;
        output.dtcFlags1[i] = (bool) ((data[index] & mask) != 0);

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
    }

    mask = 0b1;
    // setting flags for DTC#2:
    for (int i = 0; i < 16; i++)
    {
        int index = i < 8 ? 5 : 4;
        output.dtcFlags2[i] = (bool) ((data[index] & mask) != 0);

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
    }

    // setting flags for relay states:
    mask = 0b1;
    for (int i = 0; i < 16; i++)
    {
        int index = i < 8 ? 7 : 6;
        output.relayStates[i] = (bool) ((data[index] & mask) != 0);

        mask <<= 1;
        if (i == 7)
            mask = 0b1;
    }

    return output;
}

string BMS::getCurrLimitStr(int currLimitNum)
{
    return currLimitStrArr[currLimitNum];
}

string BMS::getDtcFlag1Str(int flag1)
{
    return dtcFlag1StrArr[flag1];
}

string BMS::getDtcFlag2Str(int flag2)
{
    return dtcFlag2StrArr[flag2];
}

string BMS::getPrechargeStr(int state)
{
    return prechargeStrArr[state];
}

string BMS::getRelayStateStr(int state)
{
    return relayStateArr[state];
}
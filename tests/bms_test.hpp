#ifndef __BMS_TEST__
#define __BMS_TEST__

#include <iostream>
#include "bms.h"
#include "can.h"

using namespace std;

class BMS_TEST
{
    private:

    public:
        void packInfoTest();
        void tempInfoTest();
        void parseFaultsTest();
        void parseRelayStatesTest();
};

void BMS_TEST::packInfoTest()
{
    cout << "Running packInfoTest()\n";
    cout << "----------------------------------------------\n";

    // Creating the can_frame:
    can_frame packMessage;
    packMessage.can_id = 0x300;
    packMessage.can_dlc = 8;
    
    uint8_t packMessageData[8] = {0x01, 0xFC, 0x03, 0x8A, 0x02, 0x2B, 0x01, 0x34};
    copy(begin(packMessageData), end(packMessageData), begin(packMessage.data));    // just to copy data over to the array
    cout << "ID: " << hex << packMessage.can_id << endl;
    cout << "DLC: " << dec << (int) packMessage.can_dlc << endl;
    for (int i = 0; i <= 7; i++)
        cout << "Data [" << i << "]: " << hex << (int) packMessage.data[i] << "\n";
    
    cout << "----------------------------------------------\n";
    cout << "Expected values: current: 50.8A, voltage: 90.6V, SOC: 55.5%, Pack Power: 30.8kW\n";
    // Expected Values: current: 50.8A, voltage: 90.6V, SOC: 55.5%, Pack Power: 30.8kW
    
    BMS parser;
    packInfo info = parser.parsePackInfo(packMessage.data);

    cout << "Values received from the parsing function:\n";
    cout << "Pack Current: " << info.packCurrent << " A" << endl;
    cout << "Pack Voltage: " << info.packVoltage << " V" << endl;
    cout << "Pack SOC: " << info.packSOC << "%" << endl;
    cout << "Pack Power: " << info.packPower <<" kW" << endl;
    cout << "packInfoTest() is done!\n\n";
}

void BMS_TEST::tempInfoTest()
{
    cout << "Running tempInfoTest()\n";
    cout << "----------------------------------------------\n";

    // Creating the can_frame:
    can_frame tempMessage;
    tempMessage.can_id = 0x301;
    tempMessage.can_dlc = 8;
    
    uint8_t tempMessageData[8] = {0x47, 0x00, 0x50, 0x00, 0x52, 0x00, 0x01, 0x00};
    copy(begin(tempMessageData), end(tempMessageData), begin(tempMessage.data));    // just to copy data over to the array
    cout << "ID: " << hex << tempMessage.can_id << endl;
    cout << "DLC: " << dec << (int) tempMessage.can_dlc << endl;
    for (int i = 0; i <= 7; i++)
        cout << "Data [" << i << "]: " << hex << (int) tempMessage.data[i] << "\n";
    
    cout << "----------------------------------------------\n";
    cout << "Expected values:\n Avg Temp: 71C\n Internal Temp: 80C\n Highest Temp: 82C\n Highest Temp Thermistor ID: 1\n";
    // Expected values: Avg Temp: 71C, Internal Temp: 80C, Highest Temp: 82C, Highest Temp Thermistor ID: 1

    BMS parser;
    tempInfo info = parser.parseTempInfo(tempMessage.data);

    cout << "Values received from the parsing function:\n";
    cout << "Avg Temp: " << dec << (int) info.avgTemp << " C" << endl;
    cout << "Internal Temp: " << dec << (int) info.internalTemp << " C" << endl;
    cout << "Highest Temp: " << dec << (int) info.highTemp << " C" << endl;
    cout << "Highest Temp Thermistor ID: " << dec << (int) info.highTempID << endl; 
    cout << "tempInfoTest() is done!\n\n";
}

void BMS_TEST::parseFaultsTest()
{
    cout << "Running tempInfoTest()\n";
    cout << "----------------------------------------------\n";

    // Creating the can_frame:
    can_frame faultMessage;
    faultMessage.can_id = 0x302;
    faultMessage.can_dlc = 8;
    
    uint8_t faultMessageData[8] = {0x00, 0x09, 0x00, 0x41, 0x80, 0x08, 0x80, 0x63};
    copy(begin(faultMessageData), end(faultMessageData), begin(faultMessage.data));    // just to copy data over to the array
    cout << "ID: " << hex << faultMessage.can_id << endl;
    cout << "DLC: " << dec << (int) faultMessage.can_dlc << endl;
    for (int i = 0; i <= 7; i++)
        cout << "Data [" << i << "]: " << hex << (int) faultMessage.data[i] << "\n";
    
    cout << "----------------------------------------------\n";
    cout << "Expected Faults:\n";
    cout << "Current Limit Status: DCL Reduced Due To Low SOC, DCL Reduced Due To Low Cell Voltage\n";
    cout << "DTC Status #1: P0A07 (Discharge Limit Enforcement Fault), P0A0E (Lowest Cell Voltage Too Low Fault)\n";
    cout << "DTC Status #2: P0AFA (Low Cell Voltage Fault), P0A06 (Charge Limit Enforcement Fault)\n";
    cout << "Relay States: Discharge Relay Enabled, Charge Relay Enabled, Always On ON, Is-Ready ON\n";
    // Expected values: Avg Temp: 71C, Internal Temp: 80C, Highest Temp: 82C, Highest Temp Thermistor ID: 1

    BMS parser;
    faultInfo info = parser.parseFaults(faultMessage.data);

    cout << "Faults received from the parsing function:\n";

    cout << "Current Limit Status:\n";
    for(int i = 0; i < 16; i++)
    {
        if(info.currLimitStatus[i] == 1)
            cout << parser.getCurrLimitStr(i) << ": True" << endl;
    }
    
    cout << "DTC Status #1:\n";
    for(int i = 0; i < 16; i++)
    {
        if(info.dtcFlags1[i] == 1)
            cout << parser.getDtcFlag1Str(i) << ": True" << endl;
    }

    cout << "DTC Status #2:\n";
    for(int i = 0; i < 16; i++)
    {
        if(info.dtcFlags2[i] == 1)
            cout << parser.getDtcFlag2Str(i) << ": True" << endl;
    }

    cout << "Relay States:\n";
    for(int i = 0; i < 16; i++)
    {
        if(info.relayStates[i] == 1)
            cout << parser.getRelayStateStr(i) << endl;
    }

    cout << "Precharge State: " << parser.getPrechargeStr(info.prechargeState) << endl;
    cout << "parseFaultsTest() is done!\n\n";
}
#endif
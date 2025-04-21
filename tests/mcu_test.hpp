#ifndef __MCU_TEST__
#define __MCU_TEST__

#include <iostream>
#include "mcu.h"
#include "can.h"

using namespace std;

class MCU_TEST
{
    private:
        

    public:
        void motorDataTest();
};

void MCU_TEST::motorDataTest()
{
    cout << "Running motorDataTest()\n";
    cout << "----------------------------------------------\n";
    cout << "Expected values: 3000rpm, 375A, 96V\n";

    // Create a can_frame that would represent message 1
    can_frame message1Frame;
    message1Frame.can_id = 0x69;
    message1Frame.can_dlc = 8;

    uint8_t message1Data[8] = {0xb8, 0x0b, 0x77, 0x01, 0x60, 0x00, 0x92, 0x2};
    copy(begin(message1Data), end(message1Data), begin(message1Frame.data));

    // use the canFrame that we already have and pass it into the parse function:
    MCU parser;
    MotorData mcuData = parser.parseMotorData(message1Frame.data, true);
    
    cout << "Values received from the parsing function:\n";
    cout << "RPM: " << mcuData.rpm << " rpm" << endl;
    cout << "MCU Current: " << mcuData.mcuCurrent << " A" << endl;
    cout << "MCU Voltage: " << mcuData.mcuVoltage << " V" << endl;

    cout << "MCU Faults:\n";
    for (int i = 0 ; i < 16; i++)
    {
        if(mcuData.mcuFaults[i] == 1)
            cout << "Fault " << i << " : " << parser.faultStrs[i] << endl;
    }
    cout << "motorDataTest() is done!\n\n";
}

#endif
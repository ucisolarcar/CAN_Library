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
        void throttleDataTest();
};

void MCU_TEST::motorDataTest()
{
    cout << "Running motorDataTest()\n";
    cout << "----------------------------------------------\n";
    cout << "Expected values: 3000rpm, 375A, 96V, Faults: 1, 4, 7, and 9\n";

    // Create a can_frame that would represent message 1
    can_frame message1Frame;
    message1Frame.can_id = 0x0CF11E05;
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

void MCU_TEST::throttleDataTest()
{
    cout << "Running throttleDataTest()\n";
    cout << "----------------------------------------------\n";
    cout << "Expected values:\n";
    cout << "Throttle Signal = 150\n";
    cout << "MCU Temp = 96C\n";
    cout << "Motor Temp = 100C\n";
    cout << "Feedback Forward, Command Forward\n";
    cout << "Forward Switch: True\n";
    cout << "----------------------------------------------\n";

    can_frame message2Frame;
    message2Frame.can_id = 0x0CF11F05;
    message2Frame.can_dlc = 8;
    uint8_t message2Data[8] = {0x96, 0x88, 0x82, 0x00, 0x05, 0x20, 0x00, 0x00};

    //throttle signal = 150, mcuTemp = 96, motorTemp = 100, feedback fwd, cmd fwd, 

    copy(begin(message2Data), end(message2Data), begin(message2Frame.data));

    MCU parser;
    ThrottleData mcuData = parser.parseThrottleData(message2Frame.data, true);

    cout << "Values received from the parsing function:\n";
    cout << "Throttle Signal: " << dec << (int) mcuData.mcuThrottle << endl;
    cout << "MCU Temp: " << dec << (int) mcuData.mcuTemp << "C" << endl;
    cout << "Motor Temp: " << dec << (int) mcuData.motorTemp << "C" << endl;
    cout << "Feedback Status: " << parser.feedbackStrs[mcuData.controllerStatus.statusFeedback] << endl;
    cout << "Command Status: " << parser.commandStrs[mcuData.controllerStatus.statusCmd] << endl;

    cout << "Status of Switch Signals:\n";
    for (int i = 0 ; i < 8; i++)
    {
        if(mcuData.swStatus[i] == 1)
            cout << parser.swStatusStrs[i] << ": True" << endl;
    }
    cout << "throttleDataTest() is done!\n\n";
}

#endif
#ifndef __MPPT_TEST__
#define __MPPT_TEST__

#include <iostream>

#include "can.h"
#include "mppt.h"

using namespace std;

class MPPT_Test {
    private:

    public:
        MPPT_Test() = default;
        void test();
};

void MPPT_Test::test() {
    std::cout << "MPPT TEST" << std::endl; 
    cout << "----------------------------------------------\n";

    can_frame powerFrame;
    powerFrame.can_id = 0x201;
    powerFrame.can_dlc = 8;
    // input voltage = 125
    powerFrame.data[0] = 0x00;
    powerFrame.data[1] = 0x7D;
    // input current = 45
    powerFrame.data[2] = 0x00;
    powerFrame.data[3] = 0x2D;
    // output voltage = 135
    powerFrame.data[4] = 0x00;
    powerFrame.data[5] = 0x87;
    // output current = 55
    powerFrame.data[6] = 0x04;
    powerFrame.data[7] = 0xD2;

    // currCanFrame printout:
    cout << "This is what the can_frame looks like:\n";
    cout << "ID: " << hex << powerFrame.can_id << "\n"; 
    cout << "DLC: " << (int) powerFrame.can_dlc << "\n";
    for (int i = 0; i <= 7; i++)
        cout << "Data [" << i << "]: " << hex << (int) powerFrame.data[i] << "\n";

    powerMeasurements pm;
    MPPT parser;
    pm = parser.parsePowerMeasurements(powerFrame.data, 1);
    cout << "Input voltage: " << pm.inVoltage << endl;
    cout << "Input current: " << pm.inCurrent <<endl;
    cout << "Output voltage: " << pm.outVoltage << endl;
    cout << "Output current: " << pm.outCurrent << endl;
}

#endif

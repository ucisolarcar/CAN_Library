#ifndef __MPPT_TEST__
#define __MPPT_TEST__

#include <cstdint>
#include <iostream>

#include "can.h"
#include "mppt.h"

using namespace std;

class MPPT_Test {
    private:
        void split_int16(int16_t value, uint8_t* high_byte, uint8_t* low_byte);

    public:
        MPPT_Test() = default;
        void powerTest();
        void statusTest();
};

// helper function
void MPPT_Test::split_int16(int16_t value, uint8_t* high_byte, uint8_t* low_byte) {
    *high_byte = (uint8_t)((value >> 8) & 0xFF); // Extract high 8 bits
    *low_byte = (uint8_t)(value & 0xFF);         // Extract low 8 bits
}

void MPPT_Test::powerTest() {
    std::cout << "Running powerTest() for MPPT Testing" << std::endl; 
    cout << "----------------------------------------------\n";

    powerMeasurements pm;
    MPPT parser;
    can_frame powerFrame;
    powerFrame.can_id = 0x201;
    powerFrame.can_dlc = 8;

    int16_t inputVoltage = 22 / voltageScaleFactor;
    int16_t inputCurrent = 8 / currentScaleFactor;
    int16_t outputVoltage = 24 / voltageScaleFactor;
    int16_t outputCurrent = 10 / currentScaleFactor;
    
    split_int16(inputVoltage, &powerFrame.data[0], &powerFrame.data[1]);
    split_int16(inputCurrent, &powerFrame.data[2], &powerFrame.data[3]);
    split_int16(outputVoltage, &powerFrame.data[4], &powerFrame.data[5]);
    split_int16(outputCurrent, &powerFrame.data[6], &powerFrame.data[7]);

    // currCanFrame printout:
    cout << "This is what the can_frame looks like:\n";
    cout << "ID: " << hex << powerFrame.can_id << "\n"; 
    cout << "DLC: " << (int) powerFrame.can_dlc << "\n";
    for (int i = 0; i <= 7; i++)
        cout << "Data [" << i << "]: " << hex << (int) powerFrame.data[i] << "\n";

    pm = parser.parsePowerMeasurements(powerFrame.data, 1);
    cout << "Input voltage: " << pm.inVoltage << endl;
    cout << "Input current: " << pm.inCurrent <<endl;
    cout << "Output voltage: " << pm.outVoltage << endl;
    cout << "Output current: " << pm.outCurrent << endl;
}

#endif
    
void MPPT_Test::statusTest() {
    std::cout << "Running powerTest() for MPPT Testing" << std::endl; 
    cout << "----------------------------------------------\n";

}

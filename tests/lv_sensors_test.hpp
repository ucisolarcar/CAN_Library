#ifndef LV_SENSORS
#define LV_SENSORS

#include <iostream>
#include <iomanip>      // For hex printouts
#include <iterator>     // To copy over can_frame to CAN
#include "canFloat.h"
#include"sensorFunctions.h"

using namespace std;

class LV_TEST {
private:

public:
    void currentTest();
};


void LV_TEST::currentTest() {
    cout << "Running currentTest()\n";
    cout << "----------------------------------------------\n";

    // Generating a can_frame with a current of 0.125A
    // This is representative of a can_frame we should receive for current data
    can_frame currCanFrame;
    currCanFrame.can_id = 0x702;    // CAN ID of 12V DC/DC line Current Sensor
    currCanFrame.can_dlc = 4;       // We should only send 4 bytes of data
    currCanFrame.data[0] = 0xbe;    // Setting the data frame to have the float value of 0.125A
    for (int i = 1; i <= 7; i++)
        currCanFrame.data[i] = 0;

    // currCanFrame printout:
    cout << "This is what the can_frame looks like:\n";
    cout << "ID: " << hex << currCanFrame.can_id << "\n"; 
    cout << "DLC: " << (int) currCanFrame.can_dlc << "\n";
    for (int i = 0; i <= 7; i++)
        cout << "Data [" << i << "]: " << hex << (int) currCanFrame.data[i] << "\n";

    // Now extracting the CAN from the can_frame (this is what the CANBUS to CAN struct lib will be doing):
    CAN canData;
    // copy the array of bytes from currCanFrame to the array of bytes in canData
    copy(begin(currCanFrame.data), end(currCanFrame.data), begin(canData.canBytes));
    // Finally parse the current
    SensorFunctions parser;
    parser.parseCurrent(canData, true);
}

#endif

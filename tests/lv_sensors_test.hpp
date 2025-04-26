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
    void voltageTest();
    void tempTest();
    void testGPS();
};


void LV_TEST::currentTest() {
    cout << "Running currentTest()\n";
    cout << "----------------------------------------------\n";
    cout << "Expected value: -0.125A\n";

    // Generating a can_frame with a current of -0.125A
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

    SensorFunctions parser;
    // Directly pass in the pointer to the array of data in the can_frame
    parser.parseCurrent((uint8_t*) currCanFrame.data);
    cout << "\n";
}

void LV_TEST::voltageTest() {
    cout << "Running voltageTest()\n";
    cout << "----------------------------------------------\n";
    cout << "Expected value: 12.05V\n";

    // Generating a can_frame with a voltage of 12.05V
    // This is representative of a can_frame we should receive for current data
    can_frame currCanFrame;
    currCanFrame.can_id = 0x704;    // CAN ID of 12V Supplemental Battery Voltage Sensor
    currCanFrame.can_dlc = 4;       // We should only send 4 bytes of data
    uint8_t testData[8] = {0x41, 0x40, 0xcc, 0xcd, 0, 0, 0, 0};
    copy(begin(testData), end(testData), begin(currCanFrame.data));

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
    parser.parseVoltage((uint8_t*) currCanFrame.data);
    cout << "\n";
}

void LV_TEST::tempTest()
{
    cout << "Running tempTest()\n";
    cout << "----------------------------------------------\n";
    cout << "Expected value: 72.01F\n";

    // Generating a can_frame with a temperature of 72.01F
    // This is representative of a can_frame we should receive for current data
    can_frame currCanFrame;
    currCanFrame.can_id = 0x707;    // CAN ID of Thermistor 1
    currCanFrame.can_dlc = 4;       // We should only send 4 bytes of data
    uint8_t testData[8] = {0x42, 0x90, 0x05, 0x1f, 0, 0, 0, 0};
    copy(begin(testData), end(testData), begin(currCanFrame.data));

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
    parser.parseTemp((uint8_t*) currCanFrame.data);
    cout << "\n";
}

void LV_TEST::testGPS()
{
    cout << "Running testGPS()\n";
    cout << "----------------------------------------------\n";
    cout << "Expected value: Lat 40 42.5998, Long: 74 00.4853 (maybe errors with rounding)\n";

    // Generating a can_frame with a temperature of 72.01F
    // This is representative of a can_frame we should receive for current data
    can_frame currCanFrame;
    currCanFrame.can_id = 0x709;    // CAN ID of Thermistor 1
    currCanFrame.can_dlc = 8;       // We should only send 4 bytes of data
    uint8_t testData[8] = {0x45, 0x7c, 0xa9, 0x99, 0x45, 0xe7, 0x43, 0xe2};
    copy(begin(testData), end(testData), begin(currCanFrame.data));

    // currCanFrame printout:
    cout << "This is what the can_frame looks like:\n";
    cout << "ID: " << hex << currCanFrame.can_id << "\n"; 
    cout << "DLC: " << (int) currCanFrame.can_dlc << "\n";
    for (int i = 0; i <= 7; i++)
        cout << "Data [" << i << "]: " << hex << (int) currCanFrame.data[i] << "\n";

    // Now extracting the CAN from the can_frame (this is what the CANBUS to CAN struct lib will be doing):

    // Finally parse the GPS Coordinates
    SensorFunctions parser;
    parser.parseGPS((uint8_t*) currCanFrame.data);
    cout << "\n";
}

#endif

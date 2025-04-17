#ifndef LV_SENSORS
#define LV_SENSORS

#include <iostream>
#include <iomanip>      // For hex printouts
#include <iterator>     // To copy over can_frame to CAN
#include "canFloat.h"

using namespace std;

class LV_TEST {
private:

public:
    void currentTest();
    float parseCurrent(CAN currMessage);
};

/* Process would be get can_frame from the CANBUS network
*  and then get the CAN struct (just the 8 bytes) and pass that into this library
*  
*/

/*  Alternatively just pass the can_frame in
*  
*/


void LV_TEST::currentTest() {
    cout << "Running currentTest()\n";
    cout << "----------------------------------------------\n";

    // Generating a can_frame with a current of 0.125A
    // This is representative of a can_frame we should receive for current data
    can_frame currCanFrame;
    currCanFrame.can_id = 0x702;    // CAN ID of 12V DC/DC line Current Sensor
    currCanFrame.can_dlc = 4;       // We should only send 4 bytes of data
    currCanFrame.data[0] = 0x3e;    // Setting the data frame to have the float value of 0.125A
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
    parseCurrent(canData);
}

float LV_TEST::parseCurrent(CAN currMessage) {
    cout << "Parsing the Current based off of CAN struct...\n";
    cout << "----------------------------------------------\n";
    // Creating the CanFloats object for conversion
    CanFloats converter(currMessage);

    cout << "CAN: \n";
    for (int i = 0; i <= 7; i++)
        cout << "Byte [" << i << "]: " << hex << (int) currMessage.canBytes[i] << "\n";


    // get the floats back from the 
    floatPair floats = converter.getFloats();
    cout << "Float 1: " << floats.num1 << "\n";
    cout << "Float 2: " << floats.num2 << "\n";

    float current = floats.num1;
    cout << "Current After Conversion (value that would be returned): " << current << "\n";
    return current;
}

#endif

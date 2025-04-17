#ifndef LV_SENSORS
#define LV_SENSORS

#include <iostream>
#include "canFloat.h"

using namespace std;

class LV_TEST {
private:

public:
    void currentTest();

};

/* Process would be get can_frame from the CANBUS network
*  and then get the CAN struct (just the 8 bytes) and pass that into this library
*  
*/

/*  Alternatively just pass the can_frame in
*  
*/


void LV_TEST::currentTest() {
    cout << "Running currentTest()\n\n";

    // Creating a float that will be transformed into a can_frame:
    float curr1 = 0.125; // 0.125A
    cout << "Current: " << curr1 << "\n\n";

    // Creating the CanFloats object for conversion
    CanFloats converter(curr1, 0);
    CAN convertedCAN = converter.getCAN();

    cout << "CAN: \n";
    cout << "Byte 0: " << (int)convertedCAN.byte1 << " ";
    cout << "Byte 1: " << (int)convertedCAN.byte2 << " ";
    cout << "Byte 2: " << (int)convertedCAN.byte3 << " ";
    cout << "Byte 3: " << (int)convertedCAN.byte4 << " ";
    cout << "Byte 4: " << (int)convertedCAN.byte5 << " ";
    cout << "Byte 5: " << (int)convertedCAN.byte6 << " ";
    cout << "Byte 6: " << (int)convertedCAN.byte7 << " ";
    cout << "Byte 7: " << (int)convertedCAN.byte8 << "\n";

    // get the floats back from the 
    floatPair floats = converter.canToFloats(convertedCAN);
    cout << "Float 1: " << floats.num1 << "\n";
    cout << "Float 2: " << floats.num2 << "\n";

    float current = floats.num1;
    cout << "Current After Conversion: " << current << "\n";
}

#endif

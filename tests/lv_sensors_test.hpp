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
    cout << "Test\n\n";

    // Creating a float that will be transformed into a can_frame:
    float curr1 = 0.125; // 0.125A

    cout << "Current: " << curr1 << "\n\n";
    CanFloats converter(curr1, 0);
    // issue with .getCAN()
    CAN convertedCAN = converter.getCAN();

    CAN testCAN;
    testCAN.byte1 = 0x3e;
    testCAN.byte2 = 0x0;
    testCAN.byte3 = 0;
    testCAN.byte4 = 0;
    testCAN.byte5 = 0;
    testCAN.byte6 = 0;
    testCAN.byte7 = 0;
    testCAN.byte8 = 0;

    cout << "CAN: \n";
    cout << "Byte 0: " << (int)convertedCAN.byte1 << " ";
    cout << "Byte 1: " << (int)convertedCAN.byte2 << " ";
    cout << "Byte 2: " << (int)convertedCAN.byte3 << " ";
    cout << "Byte 3: " << (int)convertedCAN.byte4 << " ";
    cout << "Byte 4: " << (int)convertedCAN.byte5 << " ";
    cout << "Byte 5: " << (int)convertedCAN.byte6 << " ";
    cout << "Byte 6: " << (int)convertedCAN.byte7 << " ";
    cout << "Byte 7: " << (int)convertedCAN.byte8 << "\n";

    //called currNull since first byte has data but second byte should be 0
    floatPair currNull = converter.canToFloats(convertedCAN);
    cout << currNull.num1 << "\n";
    float current = currNull.num1;

    cout << "Current After Conversion: " << current << "\n";


}

#endif

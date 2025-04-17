/* 

Low Voltage Sensors Library
Authors: Julius Yang, Bryan Melendez
Date: 4/11/25

*/

#ifndef SENSOR_FUNCTS 
#define SENSOR_FUNCTS 

#include <iostream> // for logging
#include <iomanip> // for formatting
#include <cmath> // for float absolute value function

#include "can.h"
#include "canFloat.h"

/*
******************************************************************************************************************
Structs:
*/

//Defining float array struct for accelerometers:
typedef struct accelDataArr
{
  float arr[3];
} accelDataArr;

//Defining int array struct for 1 decimal point for decimal breakdown
//Have it set to a max of 6 for now
typedef struct decData
{
  uint8_t arr[7] = {0};
} decData;

/*
******************************************************************************************************************
Defining the SensorFunctions Class:
*/
class SensorFunctions {

  //mainly private functions here that are used in the public functions
  //I don't think there is a need for any private variables
  private: 
    //Global Private Functions
    decData decimal_breakdown(float value, int decimalpoint);

    float canToOneFloat(uint8_t data[8], int startI, int endI);
  
  public:
    //constructor:
    SensorFunctions(); 

    accelDataArr parseAccel(CAN data, bool debug);
    float parseCurrent(CAN data, bool debug);
    floatPair parseGPS(CAN data, bool debug);
};

#endif

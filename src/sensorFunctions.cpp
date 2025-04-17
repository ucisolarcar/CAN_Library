#include "sensorFunctions.h"

//Create a SensorFunctions:
SensorFunctions::SensorFunctions()
{
}

/*
 ******************************************************************************************************************
 "Global" Private Functions:
 ******************************************************************************************************************
 */

//breakdown floating points to a specific decimal point (UP TO 6 DECIMAL POINTS!!)
decData SensorFunctions::decimal_breakdown(float value, int decimalpoint) {
    //I use a struct to make it easier to send data
    struct decData output;
    output.arr[0] = int(value);

    for (int i = 0; i < decimalpoint; i++) {
        value = value - int(value);
        value = value * 10;
        output.arr[i + 1] = int(value);
    }
    return output;
}

//NEED this for now, might not need this with the inclusion of the library
//function to convert array elements into a float value:
float SensorFunctions::canToOneFloat(uint8_t data[8], int startI, int endI)
{
    int8_t intArr[8];
    //first convert each unsigned char into a signed int of 8 bits:
    for(int i = 0; i < 8; i++)
    {
        intArr[i] = (int8_t) data[i];
    }

    //then do funny stuff
    bool negFlag = false; //flag to indicate if the number should be negative or not
    float output = 0.0;
    float multNum = 1; //float that will be multiplied by .1 for decimal places
    for(int i = startI; i <= endI; i++)
    {
        if(intArr[i] < 0 && negFlag == false)
            negFlag = true; //set the flag to true if one of the values is negative
        output += fabs(multNum * intArr[i]);
        multNum *= 0.1;
    }
    if(negFlag) //if one of the array values is negative make the whole thing negative
        output *= -1;
    return output;
}

/*
 ******************************************************************************************************************
 Public Receive Functions:
 ******************************************************************************************************************
 */

//code to translate accelerometer CAN data into x,y,z values
//Needs to return 3 floats, with only 1 decimal point precision
//returns a accelDataArr, 3 indexes, 1 for each float
accelDataArr SensorFunctions::parseAccel(can_frame msg, bool debug)
{
    float x = canToOneFloat(msg.data, 1, 2);
    float y = canToOneFloat(msg.data, 3, 4);
    float z = canToOneFloat(msg.data, 5, 6);

    accelDataArr output = {x, y, z};

    if(debug)
    {
        // Printing the CAN ID in hexadecimal format
        std::cout << "Accel Sensor ID: " << std::hex << msg.can_id << std::endl;

        // Printing out X, Y, Z axis values with 1 decimal place
        std::cout << "\tX: " << std::fixed << std::setprecision(1) << x << std::endl;
        std::cout << "\tY: " << std::fixed << std::setprecision(1) << y << std::endl;
        std::cout << "\tZ: " << std::fixed << std::setprecision(1) << z << std::endl;
    }
    return output;
}

//converts a can message to a float that represents the current sensor data
float SensorFunctions::parseCurrent(can_frame msg, bool debug)
{
    //convert data to a CAN struct:
    struct CAN can;
    can.byte1 = msg.data[0];
    can.byte2 = msg.data[1];
    can.byte3 = msg.data[2];
    can.byte4 = msg.data[3];
    can.byte5 = msg.data[4];
    can.byte6 = msg.data[5];
    can.byte7 = msg.data[6];
    can.byte8 = msg.data[7];

    CanFloats canfloats = CanFloats();

    //called currNull since first byte has data but second byte should be 0
    floatPair currNull = canfloats.canToFloats(can);
    float current = currNull.num1;
    if(debug)
    {
        // Printing the Current Sensor ID in hexadecimal format
        std::cout << "Current Sensor ID: " << std::hex << msg.can_id << std::dec << std::endl;

        // Printing out the current value with 6 decimal places
        std::cout << "\tCurrent: " << std::fixed << std::setprecision(6) << current << " A" << std::endl;
    }
    return current;
}

//converts a can message to a floatPair containing the lat long for GPS.
//Will probably have to rename it since it only handles latlong, other data might
//want to be pulled such as the speed, fix, and other GPS related data
floatPair SensorFunctions::parseGPS(can_frame msg, bool debug)
{
    //convert data to a CAN struct:
    struct CAN can;
    can.byte1 = msg.data[0];
    can.byte2 = msg.data[1];
    can.byte3 = msg.data[2];
    can.byte4 = msg.data[3];
    can.byte5 = msg.data[4];
    can.byte6 = msg.data[5];
    can.byte7 = msg.data[6];
    can.byte8 = msg.data[7];

    CanFloats canfloats = CanFloats();
    floatPair latLong = canfloats.canToFloats(can);

    if(debug)
    {
        // Printing the latitude and longitude with 4 decimal places
        std::cout << "Lat: " << std::fixed << std::setprecision(4) << latLong.num1;
        std::cout << " Long: " << std::fixed << std::setprecision(4) << latLong.num2 << std::endl;
    }

    return latLong;
}

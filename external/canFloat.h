// Header file for float to can, desktop port of Arduino CAN functions
// Edited: Bryan Melendez - 8/22/24

#ifndef CAN_FLOAT
#define CAN_FLOAT

#include <stdint.h>

// Union to faciliatate the breakdown of a float into bytes:
union floatUnion {
  float myFloat;
  uint32_t myUnsigned;
  uint8_t myBytes[4];
};

typedef union floatUnion floatUnion;

//structs:
typedef struct CAN 
{
  //7 bytes for the data
  uint8_t byte1 = 0;
  uint8_t byte2 = 0;
  uint8_t byte3 = 0;
  uint8_t byte4 = 0;
  uint8_t byte5 = 0;
  uint8_t byte6 = 0;
  uint8_t byte7 = 0;
  uint8_t byte8 = 0;
} CAN;

typedef struct floatPair 
{
  float num1 = 0;
  float num2 = 0;
} floatPair;

typedef struct bitArray
{
  bool arr[32];
} bitArray;

typedef struct byteArray
{
  bool arr[8];
} byteArray;




class CanFloats {

    private:
        floatUnion myNum1;
        floatUnion myNum2;
        CAN myCAN;

        CAN toCan(floatUnion num1, floatUnion num2);
        floatPair toFloatPair(CAN canInput);


    public:
        // To make a CanFloats:
        CanFloats(float num1, float num2);

        // To make an empty CanFloats:
        CanFloats();

        //get a can and turn it into a floatPair
        floatPair canToFloats(CAN msg);

        //To convert can to float:
        floatPair getFloats();

        //to convert float to can:
        CAN getCAN();
};

#endif

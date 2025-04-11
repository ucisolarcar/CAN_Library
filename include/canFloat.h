// Header file for float to can, desktop port of Arduino CAN functions
// Edited: Bryan Melendez - 8/22/24

#ifndef CAN_FLOAT
#define CAN_FLOAT

#include <stdint.h>

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
        float myNum1;
        float myNum2;
        CAN myCAN;

        float ConvertB32ToFloat(uint32_t b32);
        uint32_t ConvertFloatToB32(float f);
        uint8_t arrToByte(bitArray bits, int start);
        bool bitRead(uint8_t num, int bit); // implementation of arduino function
        byteArray copyBytes(uint8_t num);
        bitArray copyBits(uint32_t num);

        void bitsToByte(byteArray byteArr, int *count, uint32_t *num);
        uint32_t makeNum1(CAN canInput);
        uint32_t makeNum2(CAN canInput);

        CAN toCan(uint32_t num1, uint32_t num2);
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

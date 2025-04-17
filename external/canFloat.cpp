#include "canFloat.h"
#include <iostream>

CanFloats::CanFloats(float num1, float num2)
{
  this->myNum1.myFloat = num1;
  this->myNum2.myFloat = num2;
}

CanFloats::CanFloats()
{
  this->myNum1.myFloat = 0;
  this->myNum2.myFloat = 0;
}

floatPair CanFloats::getFloats()
{
  floatPair pair = toFloatPair(getCAN());
  return pair;
}

floatPair CanFloats::canToFloats(CAN msg)
{
  floatPair output = toFloatPair(msg);
  return output;
}

CAN CanFloats::getCAN()
{
  CAN output = toCan(myNum1, myNum2);
  return output;
}


//source: https://ucexperiment.wordpress.com/2016/02/02/floating-point-precision-or-arduino-dont-know-math/
//This converts our bit representation into a regular float that can be used by the arduino
float CanFloats::ConvertB32ToFloat(uint32_t b32)
{
  float result;
  int32_t shift;
  uint16_t bias;
 
  if (b32 == 0) 
    return 0.0;
  //pull significand
  result = (b32&0x7fffff); //mask significand
  result /= (0x800000);    //convert back to float
  result += 1.0f;          //add one back 
  //deal with the exponent
  bias = 0x7f;
  shift = ((b32>>23)&0xff) - bias;
  while (shift > 0) { 
    result *= 2.0; 
    shift--; 
  }
  while (shift < 0) { 
    result /= 2.0; 
    shift++; 
  }
  //sign
  result *= (b32>>31)&1 ? -1.0 : 1.0;
  return result;
}

//This function converts a float into our a bit representation of our custom float
uint32_t CanFloats::ConvertFloatToB32(float f) {
  float normalized;
  int16_t shift;
  int32_t sign, exponent, significand;
 
  if (f == 0.0)
    return 0; //handle this special case
  //check sign and begin normalization
  if (f < 0) { 
    sign = 1; 
    normalized = -f; 
  } else { 
    sign = 0; 
    normalized = f; 
  }
  //get normalized form of f and track the exponent
  shift = 0;
  while (normalized >= 2.0) { 
    normalized /= 2.0; 
    shift++; 
  }
  while (normalized < 1.0) { 
    normalized *= 2.0; 
    shift--; 
  }
  normalized = normalized - 1.0;
  //calculate binary form (non-float) of significand 
  significand = normalized*(0x800000 + 0.5f);
  //get biased exponent
  exponent = shift + 0x7f; //shift + bias
  //combine and return
  std::cout << "ConvertFloatToB32 output: " << ((sign<<31) | (exponent<<23) | significand);
  return (sign<<31) | (exponent<<23) | significand;
}

//starts from MSB to LSB
//Takes a bitArray and a starting index, produces a uint8_t from MSB to LSB (8 bits)
uint8_t CanFloats::arrToByte(bitArray bits, int start)
{
  int i;
  uint8_t together = 0;
  int count = 7;
  for (i = start; i >= start-7; i--){
     together += (bits.arr[i] << (count));
     count--;
  }
  return together;
}

// Replaces Arduino implementation of bitRead for desktop port of this library
bool CanFloats::bitRead(uint8_t num, int bit) {
    return (num >> bit) & 0x01;
}

byteArray CanFloats::copyBytes(uint8_t num)
{
  byteArray output;
  for(int i = 7; i >= 0; i--)
  {
    bool b = bitRead(num, i);
    output.arr[i] = b;
  }
  return output;
}

//This copies each bit of a number and puts it into an array of 32 bits that is used later
bitArray CanFloats::copyBits(uint32_t num)
{
  bitArray output;
  for(int i = 31; i >= 0; i--)
  {
    bool b = bitRead(num, i);
    output.arr[i] = b;
  }
  return output;
}

//WARNING, ACCESSES COUNT DIRECTLY
void CanFloats::bitsToByte(byteArray byteArr, int *count, uint32_t *num)
{
  for(int i = 7; i >= 0 ; i--)
  {
    *num += (((uint32_t) byteArr.arr[i]) << (*count));
    *count = *count - 1;
  }
}

//reconstruct the bit representation of the lat
uint32_t CanFloats::makeNum1(CAN canInput)
{
  uint32_t num = 0;
  int count = 31;
  byteArray byte1;
  byteArray byte2;
  byteArray byte3;
  byteArray byte4;
  byte1 = copyBytes(canInput.byte1);
  byte2 = copyBytes(canInput.byte2);
  byte3 = copyBytes(canInput.byte3);
  byte4 = copyBytes(canInput.byte4);
  //start with the sign and adding in the 4 missing bits:
  bitsToByte(byte1, &count, &num);
  bitsToByte(byte2, &count, &num);
  bitsToByte(byte3, &count, &num);
  bitsToByte(byte4, &count, &num);
  return num;
}

//reconstruct the bit representation of the lat
uint32_t CanFloats::makeNum2(CAN canInput)
{
  uint32_t num = 0;
  int count = 31;
  byteArray byte5;
  byteArray byte6;
  byteArray byte7;
  byteArray byte8;
  byte5 = copyBytes(canInput.byte5);
  byte6 = copyBytes(canInput.byte6);
  byte7 = copyBytes(canInput.byte7);
  byte8 = copyBytes(canInput.byte8);
  //start with the sign and adding in the 4 missing bits:
  bitsToByte(byte5, &count, &num);
  bitsToByte(byte6, &count, &num);
  bitsToByte(byte7, &count, &num);
  bitsToByte(byte8, &count, &num);
  return num;
}

//take the gpsCAN representation and return 2 float that represent lat and long
floatPair CanFloats::toFloatPair(CAN canInput)
{
  floatPair output;
  uint32_t num1 = makeNum1(canInput);
  uint32_t num2 = makeNum2(canInput);
  output.num1 = ConvertB32ToFloat(num1);
  output.num2 = ConvertB32ToFloat(num2);
  return output;
}

//put into form that can be sent via CANBUS:
CAN CanFloats::toCan(floatUnsigned num1, floatUnsigned num2)
{
  //initialize the struct for the CAN, and copy the bits over into an array
  CAN canOut;
  canOut.byte1 = num1.myBytes[3];
  canOut.byte2 = num1.myBytes[2];
  canOut.byte3 = num1.myBytes[1];
  canOut.byte4 = num1.myBytes[0];
  canOut.byte5 = num1.myBytes[3];
  canOut.byte6 = num1.myBytes[2];
  canOut.byte7 = num1.myBytes[1];
  canOut.byte8 = num1.myBytes[0];

  return canOut;
}

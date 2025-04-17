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

//takes the CAN message and returns 2 floats represented as a struct
floatPair CanFloats::toFloatPair(CAN canInput)
{
  floatPair output;
  floatUnion num1;
  floatUnion num2;
  // Recreate number 1
  num1.myBytes[3] = canInput.byte1;
  num1.myBytes[2] = canInput.byte2;
  num1.myBytes[1] = canInput.byte3;
  num1.myBytes[0] = canInput.byte4;

  // Recreate number 2:
  num2.myBytes[3] = canInput.byte5;
  num2.myBytes[2] = canInput.byte6;
  num2.myBytes[1] = canInput.byte7;
  num2.myBytes[0] = canInput.byte8;

  output.num1 = num1.myFloat;
  output.num2 = num2.myFloat;
  return output;
}

//put into form that can be sent via CANBUS:
CAN CanFloats::toCan(floatUnion num1, floatUnion num2)
{
  //initialize the struct for the CAN, and copy the bits over into an array
  CAN canOut;
  canOut.byte1 = num1.myBytes[3];
  canOut.byte2 = num1.myBytes[2];
  canOut.byte3 = num1.myBytes[1];
  canOut.byte4 = num1.myBytes[0];
  canOut.byte5 = num2.myBytes[3];
  canOut.byte6 = num2.myBytes[2];
  canOut.byte7 = num2.myBytes[1];
  canOut.byte8 = num2.myBytes[0];

  return canOut;
}

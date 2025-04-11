
# CanFloats Library Documentation:
**Purpose:** To faciliate and to make it easier to convert floats to 8 bytes that can be sent over CANbus. Also converts CANbus bytes back to floats.

The class is a CanFloats and as an object it holds 2 floating point numbers and a CAN struct defined as myCAN.

The 2 important structs to use are the CAN and floatPair structs. The CAN struct holds 8 bytes, from byte1-byte8. This makes it easy to send our data over CANbus.
The floatPair struct holds 2 floats, num1 and num2. This allows us to separate the 2 floats we parse from the CAN struct.

## Defined Structs:
    //CAN struct is to help separate data into 8 bytes. Each 4 representing 1 float
    typedef struct CAN
    {
      //8 bytes for the data
      uint8_t byte1 = 0;
      uint8_t byte2 = 0;
      uint8_t byte3 = 0;
      uint8_t byte4 = 0;
      uint8_t byte5 = 0;
      uint8_t byte6 = 0;
      uint8_t byte7 = 0;
      uint8_t byte8 = 0;
    };
    
    //floatPair is a struct that holds 2 float numbers
    typedef struct floatPair
    {
      float num1 = 0;
      float num2 = 0;
    };
    
    //bitArray is an array of 32 bool values, holds bits for 1 floating point number
    typedef struct bitArray
    {
      bool arr[32];
    };
    
    //byteArray holds 8 bools, each bool represents a bit in a byte
    typedef struct byteArray
    {
      bool arr[8];
    };

## Public Functions:
There are 2 constructors for a CanFloats. One where 2 floats are passed in and a default constructor with no parameters:
    
    // To make a CanFloats:
    CanFloats(float num1, float num2);
    
    // To make a default CanFloats with num1 & num2 set to 0:
    CanFloats();


- **canToFloats(CAN msg)** takes in a CAN struct and returns a floatPair. This is used when you put the data from the CANbus into the CAN struct and want to get 2 floats out of it.
You might make an empty CanFloats if you don't know the floating point numbers and call this method to get the floats.

        //get a can and turn it into a floatPair
        floatPair canToFloats(CAN msg);

- **getFloats()** requires the CanFloats object to have been defined. It will return the floatPair based off of the myCAN assigned to the CanFloats object.
**Should be used when receiving data.**

        //To convert can to float:
        floatPair getFloats();

- **getCAN()** does the opposite. Given the 2 numbers stored in the CanFloats object it will convert them into a CAN struct.
**Should be used when transmitting data**

        //to convert float to can:
        CAN getCAN();

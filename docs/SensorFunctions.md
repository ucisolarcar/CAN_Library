
# SensorFunctions Library Documentation:
**Purpose:** The purpose of this library is to abstract away the many different function calls to transmit & receive sensor data.

The class is a SensorFunctions() and it holds no data. It defines 2 structs that are used to hold data related to the accelerometer and the current sensor

## Defined Structs:
    //Defining float array struct for accelerometers:
    typedef struct accelDataArr
    {
      float arr[3];
    };
    
    //Defining int array struct for 1 decimal point for decimal breakdown
    //Have it set to a max of 6 for now
    typedef struct decData
    {
      uint8_t arr[7] = {0};
    };

## Public Functions:

### Setting Up Sensors for Arduino:
NOTE: These functions will have to be called in the setup function of the Arduino. Otherwise correct GPS setup and current sensor calibration will not happen.

- **Adafruit_GPS gpsSetup(HardwareSerial \*serialPtr):** gpsSetup takes in the hardware serial address of wherever the GPS sensor is connected to and sends initial commands

      //returns a Adafruit_GPS so that it hopefully can be used by the rest of the program
      Adafruit_GPS gpsSetup(HardwareSerial *serialPtr);
    - For example, when the GPS is hooked up to TX2 and RX2 that means the GPS is hooked up to Serial2. You will need to pass in &Serial2 as a result.
    - Also the Adafruit_GPS returned by this function will need to be stored as a variable and passed into the transmit GPS function

          //GPS setup:
          Adafruit_GPS GPS = Mega.gpsSetup(&Serial2);

- **float calibrateCurr(int currpin):** This function takes in the pin the current sensor is connected to and returns a float value. **The returned float will need be stored in a variable and passed into transmitCurr()**

### Transmitting Data:
Since the main purpose of this is to make transmiting sensor data standardized and easier most of the used functions will be for transmitting sensor data:

**NOTE:** All Functions here require the mcp2515 CAN breakout board to be passed in along with the can_frame and id used for the sensor. There is a bool that is used to print out debug messages.

- **transmitAccel:** In addition this function takes in the pin for the x, y, and z axis. It fetches the data from the accelerometer with hardcoded calibration values (might need to change this in the future) and then transmits the data.

  		//transmit Accel takes in the pins for the accelerometer along with the can id that it should transmit to
		bool transmitAccel(MCP2515 mcp2515, struct can_frame canMsg, canid_t id, int xpin, int ypin, int zpin, bool debug)

    - Data is packaged as so: 0|x1|x2|y1|y2|z1|z2|0
    - EX: an x-axis value of 0.9. x1 stores 0 and then x2 stores 9. (Data in figure below is shown in HEX)

<p align="center">
<img src="IMG_2106.PNG" alt="Figure describing how accelerometer data is stored" width="400"/>	
</p>
  
- **transmitCurr:** This function takes in the current sensor's pin number along with an offset. Will transmit current sensor data, with each byte representing a decimal point:

	**NOTE:** This function requires calibrateCurr to be called in the setup function as it is required to get an offset value to calibrate the sensor

		//transmitCurr takes in the can ID that it should be transmitting and the current sensor's pin number
        bool transmitCurr(MCP2515 mcp2515, struct can_frame canMsg, canid_t id, int currPin, float offset, bool debug)

    - Data is packaged as so: c1|c2|c3|c4|0|0|0|0
    - Where c1-c4 represents the 4 bytes needed to represent a float. Since only 1 float is needed the rest of the bytes are 0

<p align="center">
<img src="IMG_2107.PNG" alt="Figure describing how current data is stored" width="800"/>	
</p>
        

- **transmitGPS:** This function takes in an Adafruit_GPS. This is returned from gpsSetup as mentioned earlier.

		//transmitGPS takes in an Adafruit
        bool transmitGPS(MCP2515 mcp2515, Adafruit_GPS GPS, struct can_frame canMsg, canid_t id, bool debug);
		
    - Data is packaged as so: |lat|long|, where each container represents 4 bytes
    - EX: lat: 33.646 long: -117.838 is sent as |33.646|-117.838| where they are sent as floats using the CanFloat Library.
 
<p align="center">
<img src="IMG_2108.PNG" alt="Figure describing how current data is stored" width="400"/>	
</p>

### Functions to Parse Data:
These functions are used on the receiving end to parse data from **CAN**

**NOTE**: These functions have a debug parameter that is used to print data onto the Serial Monitor

- **accelDataArr parseAccel(can_frame msg, bool debug):** This function takes in a can_frame from the CANBUS controller. It will then break up the message and return a struct containing the x, y , and z g values

- **float parseCurrent(can_frame msg, bool debug):** This function takes in a can_frame and uses it to parse the **CAN** message into a float that represents the current value in Amps

- **floatPair parseGPS(can_frame msg, bool debug):** This function takes in a message from the CANBUS controller and parses it into 2 floats, one representing the lat, and the other the long. This is stored in a **floatPair** which is returned.

More information about the **CAN** and **floatPair** structs can be found [here](https://github.com/ucisolarcar/arduino-library/blob/main/Utilities/canFloat/CanFloats.md)

# What Needs to be Added:

- [X] Add functions to receive data from each type of sensor
- [X] Change at the least transmitCurr to take advantage of the canFloats library
- [ ] Need to Test GPS transmit function, did not have a chance to test that

Last updated: 6/25/24 at 11:37AM

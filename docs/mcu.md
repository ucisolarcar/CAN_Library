# MCU

In the MCU class there are 2 functions to parse the 2 messages that come out of the MCU:

## parseMotorData(uint8_t data[])

Parses data from the first MCU message 0x0CF11E05

**Input:** Takes in an array of unsigned bytes (CANBUS message)

**Output:** Returns a struct called MotorData

### MotorData:

float rpm  
- 0-6000 1 rpm/but

float mcuCurrent
- 0-4000 0.1A/bit
- Maps actual current 0-400A

float mcuVoltage
- 0-1800 0.1V/bit
- Maps actual voltage 0-180V

bool mcuFaults[16]: an array of booleans, each index represents a flagged bit. Use getFaultStr() to get associated description

## parseThrottleData(uint8_t data[])

Parses data from the second MCU message 0x0CF11F05

**Input:** Takes in an array of unsigned bytes (CANBUS message)

**Output:** Returns a struct called ThrottleData

### ThrottleData:

uint8_t mcuThrottle
- throttle signal, 0-255 maps 0-5V

uint8_t mcuTemp
- Offset 40
- actual temperature = controller temperature - 40
- 1 C/bit

uint8_t motorTemp
- Offset 30
- actual temperature = controller temperature - 30
- 1 C/bit

bool swStatus[8]: Each flagged bit coressponds to the status of various switches. Use getSwStatusStr() to get the string description for the flagged bits.

ControllerStatus controllerStatus: A struct with 2 uint8_ts:
- statusFeedback. Use getFeedbackStr() to get the status of the MCU feedback
- statusCmd. Use getCommandStr() to get the status of the MCU command
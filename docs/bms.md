# BMS

The BMS class is responsible for parsing CANBUS messages from the BMS. There are 3 messages sent from the BMS from 0x300-0x302.

-   0x300: packInfo
-   0x301: tempInfo
-   0x302: faultInfo

## parsePackInfo()

**Input:** Takes the bytes from a CANBUS message (uint8_t data[])

**Output:** Returns a packInfo struct

### packInfo:

float packVoltage
- 2 bytes
- Big Endian, take raw value and multiply by 0.1
- Steps of 0.1V

float packCurrent
- 2 bytes
- Big Endian, take raw value and multiply by 0.1
- Steps of 0.1A

float packSOC
- 2 bytes
- Big Endian, take raw value and multiply by 0.5
- Steps of 0.5%

float packPower
- 2 bytes
- Big Endian, take raw value and multiply by 0.1
- Steps of 0.1kW

## parseTempInfo()

**Input:** Takes the bytes from a CANBUS message (uint8_t data[])

**Output:** Returns a tempInfo struct

### tempInfo:

uint8_t avgTemp
- 1 byte
- Represents average temperature, 1C step

uint8_t internalTemp
- 1 byte
- Represents temperature underneath the heatsink, 1C step

uint8_t highTemp
- 1 byte
- Highest thermistor temperature, 1C step

uint8_t highTempID
- 1 byte
- Represents ID of the highest thermistor

## parseFaults

Returns a struct with boolean arrays that flag bits. Each bit that is flagged represents a different error. Errors can be translated with the getStr functions

**Input:** Takes the bytes from a CANBUS message (uint8_t data[])

**Output:** Returns a faultInfo struct

### faultInfo:

bool currLimitStatus[16]
- A boolean array that represents the bits that are flagged. Flagged bits correspond with different status messages
- To get the status messages, **pass the index** of the flagged bit into getCurrLimitStr()

bool dtcFlags1[16]
- A boolean array that represents the bits that are flagged. Flagged bits correspond with different fault messages. **There are a few reserved bits and do not confuse with DTC Status 2**
- To get the status messages, **pass the index** of the flagged bit into getDtcFlag1Str()

bool dtcFlags2[16]
- A boolean array that represents the bits that are flagged. Flagged bits correspond with different fault messages. **There are a few reserved bits and do not confuse with DTC Status 1**
- To get the status messages, **pass the index** of the flagged bit into getDtcFlag2Str()

uint8_t prechargeState
- A number that represents the state of the precharge function
- To get a string that gives a description of the state use getPrechargeStr()
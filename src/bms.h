#ifndef __BMS_H__
#define __BMS_H__

#include <iostream> // TODO make sure this compiles in arduino
#include <cstdint>

#include "can.h"
#include "canFloat.h"

using namespace std;

/* 
    3 messages that will be sent by BMS. 3 functions to parse each of the messages:
    -   0x300: packInfo
    -   0x301: tempInfo
    -   0x302: faultInfo
*/

// In order to normalize and faciliate the correct truncation of the float
// these "factors" will be used. Ensures that we aren't getting extra precision
const int tempFactor = 1;
const float currentFactor = 0.1;
const float voltageFactor = 0.1;
const float packFactor = 0.1;
const float socFactor = 0.1;

// 0x300
typedef struct packInfo {
    float packVoltage;
    float packCurrent;
    float packSOC;
    float packPower;
} packInfo;

// 0x301
typedef struct tempInfo {
    uint8_t avgTemp;
    uint8_t internalTemp;
    uint8_t highTemp;
    uint8_t highTempID;     // returns the ID of the thermistor detecting the highest temp reading
} tempInfo;

// 0x302
typedef struct faultInfo {
    bool currLimitStatus[16];
    bool dtcFlags1[16];
    bool dtcFlags2[16];
    bool relayStates[16];
    uint8_t prechargeState; // No longer using
} faultInfo;

class BMS {
    private:
        // Strings that correspond with the fault messages:
        string currLimitStrArr[16] = { 
            "DCL Reduced Due To Low SOC", "DCL Reduced Due To High Cell Resistance",
            "DCL Reduced Due To Temperature", "DCL Reduced Due To Low Cell Voltage",
            "DCL Reduced Due To Low Pack Voltage", "Reserved",
            "DCL and CCL Reduced Due To Voltage Failsafe", "DCL and CCL Reduced Due To Communication Failsafe (For multiple BMS units)",
            "Reserved", "CCL Reduced Due To High SOC",
            "CCL Reduced Due To High Cell Resistance", "CCL Reduced Due To Temperature", 
            "CCL Reduced Due To High Cell Voltage", "CCL Reduced Due To High Pack Voltage", 
            "CCL Reduced Due To Charger Latch", "CCL Reduced Due To Alternate Current Limit [MPI]"
        };

        string dtcFlag1StrArr[16] = {
            "P0A07 (Discharge Limit Enforcement Fault)", "P0A08 (Charger Safety Relay Fault)",
            "P0A09 (Internal Hardware Fault)", "P0A0A (Internal Heatsink Thermistor Fault)",
            "P0A0B (Internal Software Fault)", "P0A0C (Highest Cell Voltage Too High Fault)",
            "P0A0E (Lowest Cell Voltage Too Low Fault)", "P0A10 (Pack Too Hot Fault)",
            "P0A95 (High Voltage Interlock Signal Fault)", "P0AA1 (Precharge Circuit Malfunction)",
            "P0A11 (Abnormal State of Charge Behavior)", "RESERVED",
            "RESERVED", "RESERVED",
            "RESERVED", "RESERVED"
        };

        string dtcFlag2StrArr[16] = {
            "P0A1F (Internal Communication Fault)", "P0A12 (Cell Balancing Stuck Off Fault)",
            "P0A80 (Weak Cell Fault)", "P0AFA (Low Cell Voltage Fault)",
            "P0A04 (Open Wiring Fault)", "P0AC0 (Current Sensor Fault)",
            "P0A0D (Highest Cell Voltage Over 5V Fault)", "P0A0F (Cell ASIC Fault)",
            "P0A02 (Weak Pack Fault)", "P0A81 (Fan Monitor Fault)", 
            "P0A9C (Thermistor Fault)", "U0100 (External Communication Fault)",
            "P0560 (Redundant Power Supply Fault)", "P0AA6 (High Voltage Isolation Fault)",
            "P0A05 (Input Power Supply Fault)", "P0A06 (Charge Limit Enforcement Fault)"
        };

        string prechargeStrArr[11] = {
            "Precharge waiting for activation (OFF)", "Stage 1: Check HVPOS Contact",
            "Stage 2: Delay during HVPOS Check", "Stage 3: Close HVNEG Contact",
            "Stage 4: Precharge Relay On", "Stage 5: Precharge Delay Start",
            "Stage 6: Precharge Delay End", "Stage 7: Close HVPOS Contact",
            "Stage 8: Precharge Relay Off", "Stage 9: Precharge Complete / Success",
            "ERROR: Precharge FAULT / UNSUCCESSFUL"
        };

        string relayStateArr[16] = {
            "Discharge Relay Enabled", "Charge Relay Enabled",
            "Charger Safety Enabled", "Malfunction Indicator Active (DTC status)",
            "Multi-Purpose Input Signals ON", "Always On ON",
            "Is-Ready ON", "Is-Charging ON",

            "Multi-Purpose Input 2 ON", "Multi-Purpose Input 3 ON",
            "Reserved", "Multi-Purpose Output 2 ON",
            "Multi-Purpose Output 3 ON", "Multi-Purpose Output 4 ON",
            "Multi-Purpose Output Enable ON", "Multi-Purpose Output 1 ON"
        };
        

        int16_t combineBytes(uint8_t high, uint8_t low);

    public:
        // constructor:
        BMS();

        packInfo parsePackInfo(uint8_t data[]);

        tempInfo parseTempInfo(uint8_t data[]);

        faultInfo parseFaults(uint8_t data[]);

        // getter functions for message strings:
        string getCurrLimitStr(int currLimitNum);
        string getDtcFlag1Str(int flag1);
        string getDtcFlag2Str(int flag2);
        string getPrechargeStr(int state);
        string getRelayStateStr(int stateNum);
};

#endif
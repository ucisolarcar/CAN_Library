#include "mppt.h"
#include <cstdint>

int16_t MPPT::combineBytes(uint8_t high, uint8_t low) {
    return static_cast<int16_t>((high << 8) | low);
}

powerMeasurements MPPT::parsePowerMeasurements(uint8_t data[], bool debug) {
    powerMeasurements pm;

    pm.inVoltage = (float)combineBytes(data[0], data[1]) * voltageScaleFactor; 
    pm.inCurrent = (float)combineBytes(data[2], data[3]) * currentScaleFactor;
    pm.outVoltage = (float)combineBytes(data[4], data[5]) * voltageScaleFactor;
    pm.outCurrent = (float)combineBytes(data[6], data[7]) * currentScaleFactor;

    // debug

    return pm;
}

mpptStatus MPPT::parseMPPTStatus(uint8_t data[], bool debug) {
    mpptStatus status;

    status.mode = (int)data[0];
    status.fault = (int)data[1];
    status.enabled = (bool)data[2];

    status.ambientTemp = static_cast<int>(static_cast<int8_t>(data[3]));
    status.heatsinkTemp = (int)(int8_t)data[4];

    // debug

    return status;
}

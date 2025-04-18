#include "mppt.h"
#include <cstdint>

int16_t MPPT::combineBytes(uint8_t high, uint8_t low) {
    return static_cast<int16_t>((high << 8) | low);
}

powerMeasurements MPPT::parsePowerMeasurements(uint8_t data[], bool debug) {
    powerMeasurements pm;

    pm.inVoltage = combineBytes(data[0], data[1]) / voltageScaleFactor; 
    pm.inCurrent = combineBytes(data[2], data[3]) / currentScaleFactor;
    pm.outVoltage = combineBytes(data[4], data[5]) / voltageScaleFactor;
    pm.outCurrent = combineBytes(data[6], data[7]) / currentScaleFactor;

    // debug

    return pm;
}

mpptStatus MPPT::parseMPPTStatus(uint8_t data[], bool debug) {
    mpptStatus status;

    status.mode = data[0];
    status.fault = data[1];
    status.enabled = (bool)data[2];

    int8_t a_tempConverted = (int8_t)data[3];
    status.ambientTemp = (int)a_tempConverted;

    int8_t h_tempConverted = (int8_t)data[4];
    status.heatsinkTemp = (int)h_tempConverted;

    // debug

    return status;
}

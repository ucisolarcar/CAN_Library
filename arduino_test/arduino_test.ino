#include <Arduino.h>

#include "../src/sensorFunctions.h"
#include "../src/mppt.h"
#include "../src/mcu.h"

setup() {
  Serial.begin(9600);

  MPPT mppt;
  MCU mcu;
  SensorFunctions sensfuncs;
}

loop() {
  Serial.println("testing");
}

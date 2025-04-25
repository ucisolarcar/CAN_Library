#line 1 "/home/bryan/projects/solar_car/CAN_Library/arduino_test/arduino_test.ino"
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


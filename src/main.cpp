#include <Arduino.h>
#include "DroneController/DroneController.h"

DroneController *droneController;
// uint32_t previousPrintTime = 0;

void setup() {
  droneController = new DroneController();
  Serial.begin(19200);
  delay(250);
}

void loop() {
  droneController->Loop();
  // uint32_t currentTime = millis();
  // if (currentTime - previousPrintTime > 1000)
  // {
  //   Serial.begin(19200);
  //   Serial.println(int(currentTime));
  //   previousPrintTime = currentTime;
  // }
}
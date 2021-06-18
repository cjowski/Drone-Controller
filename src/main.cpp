#include <Arduino.h>
#include "DroneController/DroneController.h"

// #include "Board/NucleoL476rg/NucleoL476rgSetup.h"
// BoardSetup *boardSetup = new NucleoL476rgSetup();

#include "Board/BluePill/BluePillSetup.h"
BoardSetup *boardSetup = new BluePillSetup();

DroneController *droneController;
uint32_t previousPrintTime = 0;

void setup() {
  Serial.begin(19200);
  delay(250);
  droneController = new DroneController(boardSetup);
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
#include <Arduino.h>
#include "DroneController/DroneController.h"

// #include "Board/NucleoL476rg/NucleoL476rgSetup.h"
// BoardSetup *boardSetup = new NucleoL476rgSetup();

// #include "Board/BluePill/BluePillSetup.h"
// BoardSetup *boardSetup = new BluePillSetup();

#include "Board/BlackPill/BlackPillSetup.h"
BoardSetup *boardSetup = new BlackPillSetup();

DroneController *droneController;
uint32_t previousPrintTime = 0;

void setup() {
  delay(250);
  droneController = new DroneController(boardSetup);
  delay(250);
  Serial.begin(19200);
}

void loop() {
  droneController->Loop();
  // uint32_t currentTime = millis();
  // if (currentTime - previousPrintTime > 1000)
  // {
  //   Serial.println(int(currentTime));
  //   previousPrintTime = currentTime;
  // }
}
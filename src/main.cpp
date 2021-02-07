#include <Arduino.h>
#include "DroneController/DroneController.h"

DroneController *droneController = new DroneController();

void setup() {
  droneController->Setup();
  delay(250);
}

void loop() {
  droneController->Loop();
  droneController->SerialPrint();
}
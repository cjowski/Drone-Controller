#include <Arduino.h>
#include "DroneController/DroneController.h"

DroneController *droneController;

void setup() {
  droneController = new DroneController();
  delay(250);
}

void loop() {
  droneController->Loop();
}
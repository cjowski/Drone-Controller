#include "DroneController.h"

DroneController::DroneController()
{
  MyFmController = new FmController();
  MyGyroController = new GyroController();
  MyTaskController = new TaskController();
  MySerialController = new SerialController(
    [&] () -> SerialValue* {
      return MyFmController->GetSerialValue();
    },
    [&] () -> SerialValue* {
      return MyGyroController->GetSerialValue();
    },
    MyTaskController
  );
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  MySerialController->Loop();
  MyTaskController->Loop();
}
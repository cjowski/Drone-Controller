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
  MyMotor = new Motor(
    FmChannel::MIN_VALUE,
    FmChannel::MAX_VALUE,
    [&] () -> bool {
      return MyFmController->GetFmSignalState() == FmChannel::active;
    },
    [&] () -> int {
      return MyFmController->GetFmChannelValue(2);
    }
  );
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  MySerialController->Loop();
  MyTaskController->Loop();
  MyMotor->Loop();
}
#include "DroneController.h"

DroneController::DroneController()
{
  MyFmController = new FmController();
  MyGyroController = new GyroController();
  MyMotorController = new MotorController(
    new MotorModeChannelMap(
      FmChannel::MIN_VALUE,
      FmChannel::MAX_VALUE,
      [&] () -> bool {
        return MyFmController->GetFmSignalState() == FmChannel::active;
      },
      [&] () -> int {
        return MyFmController->GetFmChannelValue(2);
      }
    )
  );
  MyTaskController = new TaskController();
  MySerialController = new SerialController(
    [&] () -> SerialValue* {
      return MyFmController->GetSerialValue();
    },
    [&] () -> SerialValue* {
      return MyGyroController->GetSerialValue();
    },
    [&] () -> SerialValue* {
      return MyMotorController->GetSerialValue();
    },
    MyTaskController
  );
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  MyMotorController->Loop();
  MySerialController->Loop();
  MyTaskController->Loop();
}
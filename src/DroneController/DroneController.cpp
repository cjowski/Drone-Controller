#include "DroneController.h"

DroneController::DroneController(
  BoardSetup *boardSetup
)
{
  MyFmController = new FmController(boardSetup->FM_BOARD_TIMER());
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
    ),
    boardSetup->MOTOR_BOARD_TIMER()
  );
  MyTaskController = new TaskController();
  MySerialController = new SerialController(
    boardSetup->ESP_COMMUNICATION_SERIAL(),
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
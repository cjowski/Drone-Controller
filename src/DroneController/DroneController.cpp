#include "DroneController.h"

DroneController::DroneController(
  BoardSetup *boardSetup
)
{
  MyFmController = new FmController(boardSetup->FmBoardTimerSetup);
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
    boardSetup->MotorBoardTimer
  );

  HardwareSerial* communicationSerial = new HardwareSerial(
    boardSetup->EspCommunicationSerial->RX_PIN(),
    boardSetup->EspCommunicationSerial->TX_PIN()
  );

  SerialPrinter *printer = new SerialPrinter(
    new StringListEncoder(false),
    communicationSerial,
    SERIAL_BAUD_RATE
  );

  SerialReader *reader = new SerialReader(
    new StringListDecoder(true),
    communicationSerial,
    SERIAL_BAUD_RATE
  );

  MyTaskController = new TaskController(printer, true);
  MySerialController = new SerialController(
    printer,
    reader,
    [&] () -> SerialEncoderInput* {
      return MyFmController->GetSerialEncoderInput();
    },
    [&] () -> SerialEncoderInput* {
      return MyGyroController->GetSerialEncoderInput();
    },
    [&] () -> SerialEncoderInput* {
      return MyMotorController->GetSerialEncoderInput();
    },
    MyTaskController
  );
}

void DroneController::Setup()
{
  MyFmController->Setup();
  MyGyroController->Setup();
  MyMotorController->Setup();
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  MyMotorController->Loop();
  MySerialController->Loop();
  MyTaskController->Loop();
}
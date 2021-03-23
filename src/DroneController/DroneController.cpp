#include "DroneController.h"

DroneController::DroneController()
{
  MyFmController = new FmController();
  MyGyroController = new GyroController();
  MySerialPrintController = new SerialPrintController(
    SERIAL3_RX_PIN,
    SERIAL3_TX_PIN,
    SERIAL_BAUD_RATE,
    [&] ()->std::list<String> {
      return MyFmController->GetPrintStrings();
    },
    [&] ()->std::list<String> {
      return MyGyroController->GetPrintStrings();
    }
  );
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  MySerialPrintController->Print();
}
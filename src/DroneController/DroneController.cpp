#include "DroneController.h"

DroneController::DroneController()
{
  MyFmController = new FmController();
  MyGyroController = new GyroController();
  HardwareSerial* stmEspSerial = new HardwareSerial(SERIAL3_RX_PIN, SERIAL3_TX_PIN);
  MySerialPrintController = new SerialPrintController(
    stmEspSerial,
    SERIAL_BAUD_RATE,
    [&] ()->std::list<String> {
      return MyFmController->GetPrintStrings();
    },
    [&] ()->std::list<String> {
      return MyGyroController->GetPrintStrings();
    }
  );
  MySerialReader = new SerialStringReader(stmEspSerial);
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  MySerialPrintController->Print();
  MySerialReader->Read();
}
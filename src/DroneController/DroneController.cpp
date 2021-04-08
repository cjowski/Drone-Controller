#include "DroneController.h"

DroneController::DroneController()
{
  MyFmController = new FmController();
  MyGyroController = new GyroController();
  HardwareSerial* stmEspSerial = new HardwareSerial(SERIAL3_RX_PIN, SERIAL3_TX_PIN);
  SerialPrinter* serialPrinter = new SerialPrinter(stmEspSerial, SERIAL_BAUD_RATE);

  MySerialPrintControllers.push_back(
    new SerialPrintController(
      serialPrinter,
      50,
      [&] () -> SerialValue* {
        return MyFmController->GetSerialValue();
      }
    )
  );

  MySerialPrintControllers.push_back(
    new SerialPrintController(
      serialPrinter,
      120,
      [&] () -> SerialValue* {
        return MyGyroController->GetSerialValue();
      }
    )
  );

  MySerialReader = new SerialReader(stmEspSerial);
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  for (auto it = MySerialPrintControllers.begin(); it != MySerialPrintControllers.end(); it++)
  {
    (*it)->Loop();
  }
  MySerialReader->Read();
}
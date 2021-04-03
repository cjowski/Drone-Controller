#include "SerialPrintController.h"

SerialPrintController::SerialPrintController(
  HardwareSerial *printerSerial,
  int serialBaudRate,
  std::function<std::list<String>(void)> getFmStrings,
  std::function<std::list<String>(void)> getGyroStrings
)
{
  PrinterSerial = printerSerial;
  SerialBaudRate = serialBaudRate;

  SerialPrinterFm = new SerialPrinter(
    PrinterSerial,
    getFmStrings,
    FM_PRINT_KEY,
    FM_PRINT_DELAY
  );

  SerialPrinterGyro = new SerialPrinter(
    PrinterSerial,
    getGyroStrings,
    GYRO_PRINT_KEY,
    GYRO_PRINT_DELAY
  );
}

void SerialPrintController::Print()
{
  PrinterSerial->begin(SerialBaudRate);
  SerialPrinterFm->SerialPrintln();
  SerialPrinterGyro->SerialPrintln();
  PrinterSerial->flush();
}
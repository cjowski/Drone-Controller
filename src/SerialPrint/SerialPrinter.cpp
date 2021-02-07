#include "SerialPrinter.h"

SerialPrinter::SerialPrinter(
  HardwareSerial *printerSerial,
  std::function<String(void)> getSerialStringCallback,
  int printDelay
)
{
  PrinterSerial = printerSerial;
  GetSerialStringCallback = getSerialStringCallback;
  PrintDelay = printDelay;
  PreviousPrintTime = 0;
}

void SerialPrinter::SerialPrintln()
{
  uint32_t currentTime = millis();
  if (currentTime - PreviousPrintTime > PrintDelay) {
    PrinterSerial->println(
      GetSerialStringCallback()
    );

    PreviousPrintTime = currentTime;
  }
}
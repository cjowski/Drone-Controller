#include "SerialPrintController.h"

SerialPrintController::SerialPrintController(
  SerialPrinter *mySerialPrinter,
  int printDelay,
  std::function<SerialValue*(void)> getSerialValue
)
{
  PrintDelay = printDelay;
  MySerialPrinter = mySerialPrinter;
  GetSerialValue = getSerialValue;
}

void SerialPrintController::Loop()
{
  uint32_t currentTime = millis();
  if (currentTime - PreviousPrintTime > PrintDelay) {
    MySerialPrinter->Begin();
    SerialValue *serialValue = GetSerialValue();
    MySerialPrinter->Println(serialValue);
    MySerialPrinter->Flush();
    PreviousPrintTime = currentTime;
    delete serialValue;
  }
}
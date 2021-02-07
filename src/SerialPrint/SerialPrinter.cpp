#include "SerialPrinter.h"

SerialPrinter::SerialPrinter(
  HardwareSerial *printerSerial,
  std::function<std::list<String>(void)> getSerialStringCallback,
  char printKey,
  int printDelay
)
{
  PrinterSerial = printerSerial;
  GetStringListCallback = getSerialStringCallback;
  PrintKey = printKey;
  PrintDelay = printDelay;
  PreviousPrintTime = 0;
}

void SerialPrinter::SerialPrintln()
{
  uint32_t currentTime = millis();
  if (currentTime - PreviousPrintTime > PrintDelay) {

    PrinterSerial->println(
      GetPrintString()
    );

    PreviousPrintTime = currentTime;
  }
}

String SerialPrinter::GetPrintString()
{
  std::list<String> stringList = GetStringListCallback();
  String outputString = "";
  char wordSeparator = 'a';

  outputString += "[" + String(PrintKey) + "]";

  std::list<String>::iterator it;
  for (it = stringList.begin(); it != stringList.end(); it++)
  {
    outputString += *it;
    
    if (std::next(it) != stringList.end())
    {
      outputString += (wordSeparator++);
    }
  }
  
  return "<" + outputString + ">";
}
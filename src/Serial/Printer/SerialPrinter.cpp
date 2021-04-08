#include "SerialPrinter.h"

SerialPrinter::SerialPrinter(
  HardwareSerial *printSerial,
  int serialBaudRate
)
{
  PrintSerial = printSerial;
  SerialBaudRate = serialBaudRate;
}

void SerialPrinter::Begin()
{
  PrintSerial->begin(SerialBaudRate);
}

void SerialPrinter::Print(SerialValue *value)
{
  PrintSerial->print(value->ToSerialString());
}

void SerialPrinter::Println(SerialValue *value)
{
  PrintSerial->println(value->ToSerialString());
}

void SerialPrinter::Flush()
{
  PrintSerial->flush();
}
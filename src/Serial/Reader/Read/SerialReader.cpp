#include "SerialReader.h"

SerialReader::SerialReader(HardwareSerial *readSerial)
{
  ReadSerial = readSerial;
  RecentReadValue = new SerialReadValue();
}

SerialReadValue* SerialReader::GetRecentReadValue()
{
  return RecentReadValue;
}
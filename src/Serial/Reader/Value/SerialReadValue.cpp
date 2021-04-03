#include "SerialReadValue.h"

SerialReadValue::SerialReadValue()
{
  TextValue = "";
}

bool SerialReadValue::Equals(SerialReadValue valueToCompare)
{
  return TextValue.equals(valueToCompare.ToString());
}

void SerialReadValue::SetNewTextValue(char serialPrintKey, String newTextValue)
{
  SerialPrintKey = serialPrintKey;
  TextValue = newTextValue;
}

char SerialReadValue::GetSerialPrintKey()
{
  return SerialPrintKey;
}

String SerialReadValue::ToString()
{
  if (!TextValue.equals(""))
  {
    return TextValue;
  }
  else
  {
    return SERIAL_TEXT_VALUE_EMPTY;
  }
}
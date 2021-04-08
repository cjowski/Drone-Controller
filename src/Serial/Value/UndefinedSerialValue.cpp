#include "UndefinedSerialValue.h"

UndefinedSerialValue::UndefinedSerialValue(char readValueKey, std::list<String> values)
{
  ReadValueKey = readValueKey;
  Values = values;
}

std::list<String> UndefinedSerialValue::GetPrintStrings()
{
  return Values;
}

char UndefinedSerialValue::GetReadValueKey()
{
  return ReadValueKey;
}

bool UndefinedSerialValue::Exists()
{
  return ReadValueKey != SERIAL_VALUE_KEY();
}
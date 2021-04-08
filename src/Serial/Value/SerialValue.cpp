#include "SerialValue.h"

String SerialValue::ToSerialString()
{
  String outputString =
    SerialValueConstants::VALUE_KEY_START_TAG
    + String(SERIAL_VALUE_KEY())
    + SerialValueConstants::VALUE_KEY_END_TAG;

  std::list<String> printStrings = GetPrintStrings();
  char currentWordSeparator = SerialValueConstants::FIRST_WORD_SEPARATOR;

  for (auto it = printStrings.begin(); it != printStrings.end(); it++)
  {
    outputString += *it;
    
    if (std::next(it) != printStrings.end())
    {
      outputString += (currentWordSeparator++);
    }
  }
  
  return SerialValueConstants::STRING_START_TAG
    + outputString
    + SerialValueConstants::STRING_END_TAG;
}

bool SerialValue::SerialValueValid(char serialReadKey, std::list<String> serialValues)
{
  return SerialReadKeyMatched(serialReadKey)
    && SerialValuesMatched(serialValues);
}

bool SerialValue::SerialReadKeyMatched(char serialReadKey)
{
  return serialReadKey == SERIAL_VALUE_KEY();
}
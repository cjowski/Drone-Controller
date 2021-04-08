#include "SerialReader.h"

SerialReader::SerialReader(HardwareSerial *readSerial)
{
  ReadSerial = readSerial;
}

UndefinedSerialValue SerialReader::Read()
{
  char receivedKey = 'U';
  char *receivedWordChars = new char[INPUT_STRING_SIZE];
  std::list<String> receivedStrings;
  int currentReadIndex = 0;
  int wordLength = 0;
  bool receivingInProgress = false;
  bool receivingKeyInProgress = false;
  char readCharacter;
  char nextWordSeparator = SerialValueConstants::FIRST_WORD_SEPARATOR;
  
  while (ReadSerial->available() > 0) {

    if (currentReadIndex >= INPUT_STRING_SIZE)
    {
      currentReadIndex = 0;
      break;
    }

    readCharacter = ReadSerial->read();

    if (IsWordSeparator(readCharacter)) {
      if (readCharacter != nextWordSeparator) {
        break;
      }
      nextWordSeparator++;
    }

    if (receivingInProgress) {
      if (readCharacter == SerialValueConstants::VALUE_KEY_START_TAG) {
        receivingKeyInProgress = true;
      }
      else if (receivingKeyInProgress && readCharacter != SerialValueConstants::VALUE_KEY_END_TAG) {
        receivedKey = readCharacter;
      }
      else if (readCharacter == SerialValueConstants::VALUE_KEY_END_TAG) {
        receivingKeyInProgress = false;
      }
      else if (readCharacter != SerialValueConstants::STRING_END_TAG) {
        if (IsWordSeparator(readCharacter))
        {
          receivedStrings.push_back(
            GetStringFromChars(receivedWordChars, wordLength)
          );
          delete receivedWordChars;
          receivedWordChars = new char[INPUT_STRING_SIZE];
          wordLength = 0;
        }
        else
        {
          receivedWordChars[wordLength] = readCharacter;
          wordLength++;
        }
        currentReadIndex++;
      }
      else {
        receivingInProgress = false;
        currentReadIndex = 0;
        receivedStrings.push_back(
          GetStringFromChars(receivedWordChars, wordLength)
        );
        break;
      }
    }
    else if (readCharacter == SerialValueConstants::STRING_START_TAG) {
      receivingInProgress = true;
      currentReadIndex = 0;
    }
  }

  delete receivedWordChars;
  return UndefinedSerialValue(receivedKey, receivedStrings);
}

bool SerialReader::IsWordSeparator(char character)
{
  return character >= SerialValueConstants::FIRST_WORD_SEPARATOR
    && character <= SerialValueConstants::LAST_WORD_SEPARATOR;
}

String SerialReader::GetStringFromChars(char *chars, int arrayLength)
{
  String outputString = "";
  for (int i = 0; i < arrayLength; i++)
  {
    outputString += chars[i];
  }
  return outputString;
}
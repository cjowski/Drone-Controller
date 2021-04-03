#include "SerialStringReader.h"

void SerialStringReader::Read()
{
  int currentReadIndex = 0;
  bool receivingInProgress = false;
  bool receivingKeyInProgress = false;
  char readCharacter;
  char nextWordSeparator = FIRST_WORD_SEPARATOR;
  while (ReadSerial->available() > 0) {
    if (currentReadIndex >= INPUT_STRING_SIZE)
    {
      currentReadIndex = 0;
      break;
    }

    readCharacter = ReadSerial->read();
    Serial2.println(readCharacter);

    if (IsWordSeparator(readCharacter)) {
      if (readCharacter != nextWordSeparator) {
        break;
      }
      nextWordSeparator++;
    }

    if (receivingInProgress) {
      if (readCharacter == KEY_START_MARKER) {
        receivingKeyInProgress = true;
      }
      else if (receivingKeyInProgress && readCharacter != KEY_END_MARKER) {
        ReceivedKey = readCharacter;
      }
      else if (readCharacter == KEY_END_MARKER) {
        receivingKeyInProgress = false;
      }
      else if (readCharacter != END_MARKER) {
        SetReceivedChar(readCharacter, currentReadIndex);
        currentReadIndex++;
      }
      else {
        SetReceivedChar('\0', currentReadIndex);
        receivingInProgress = false;
        currentReadIndex = 0;
        //Serial.println(ReceivedChars);
        RecentReadValue->SetNewTextValue(ReceivedKey, ReceivedChars);
        break;
      }
    }
    else if (readCharacter == START_MARKER) {
      receivingInProgress = true;
      currentReadIndex = 0;
    }
  }
}

bool SerialStringReader::IsWordSeparator(char character)
{
  return character >= FIRST_WORD_SEPARATOR && character <= LAST_WORD_SEPARATOR;
}

void SerialStringReader::SetReceivedChar(char character, int index)
{
  if (IsWordSeparator(character)) {
    ReceivedChars[index] = ' ';
  }
  else {
    ReceivedChars[index] = character;
  }
}
#ifndef SERIAL_STRING_READER_H
#define SERIAL_STRING_READER_H

  #include "Serial/Reader/Read/SerialReader.h"
  #include <WString.h>

  #define INPUT_STRING_SIZE 50

  class SerialStringReader : public SerialReader
  {
    private:
    char ReceivedKey;
    char ReceivedChars[INPUT_STRING_SIZE];
    const char START_MARKER = '<';
    const char END_MARKER = '>';
    const char KEY_START_MARKER = '[';
    const char KEY_END_MARKER = ']';
    const char FIRST_WORD_SEPARATOR = 'a';
    const char LAST_WORD_SEPARATOR = 'z';

    bool IsWordSeparator(char character);
    void SetReceivedChar(char character, int index);

    public:
    SerialStringReader(HardwareSerial *readSerial) : SerialReader(readSerial) { };
    virtual void Read();
  };

#endif
#ifndef SERIAL_READER_H
#define SERIAL_READER_H

  #include <HardwareSerial.h>
  #include "Serial/Value/UndefinedSerialValue.h"

  class SerialReader
  {
    private:
    HardwareSerial *ReadSerial;
    const int INPUT_STRING_SIZE = 50;

    bool IsWordSeparator(char character);
    String GetStringFromChars(char *chars, int arrayLength);

    public:
    SerialReader() { };
    SerialReader(HardwareSerial *readSerial);
    UndefinedSerialValue Read();
  };

#endif
#ifndef SERIAL_READER_H
#define SERIAL_READER_H

  #include <HardwareSerial.h>
  #include "Serial/Reader/Value/SerialReadValue.h"

  class SerialReader
  {
    public:
    SerialReader() { };
    SerialReader(HardwareSerial *readSerial);
    virtual void Read() = 0;
    SerialReadValue* GetRecentReadValue();

    protected:
    HardwareSerial *ReadSerial;
    SerialReadValue *RecentReadValue;
  };

#endif
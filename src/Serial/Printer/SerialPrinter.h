#ifndef SERIAL_PRINTER_H
#define SERIAL_PRINTER_H

  #include <HardwareSerial.h>
  #include <WSerial.h>
  #include "Serial/Value/SerialValue.h"

  class SerialPrinter
  {
    private:
    HardwareSerial *PrintSerial;
    int SerialBaudRate;
    
    public:
    SerialPrinter(HardwareSerial *printSerial, int serialBaudRate);
    void Begin();
    void Print(SerialValue *value);
    void Println(SerialValue *value);
    void Flush();
  };

#endif
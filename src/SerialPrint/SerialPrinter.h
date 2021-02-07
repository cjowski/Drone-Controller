#ifndef SERIAL_PRINTER_H
#define SERIAL_PRINTER_H

  #include <WSerial.h>
  #include <WString.h>
  #include <functional>
  #include <list>
  #include <wiring_time.h>

  class SerialPrinter
  {
    private:
    HardwareSerial *PrinterSerial;
    std::function<std::list<String>(void)> GetStringListCallback;
    char PrintKey;

    uint32_t PrintDelay;
    uint32_t PreviousPrintTime;

    String GetPrintString();

    public:
    SerialPrinter(
      HardwareSerial *printerSerial,
      std::function<std::list<String>(void)> getStringListCallback,
      char printKey,
      int printDelay
    );
    void SerialPrintln();
  };

#endif
#ifndef SERIAL_PRINTER_H
#define SERIAL_PRINTER_H

  #include <WSerial.h>
  #include <WString.h>
  #include <functional>
  #include <wiring_time.h>

  class SerialPrinter
  {
    private:
    HardwareSerial *PrinterSerial;
    std::function<String(void)> GetSerialStringCallback;

    int PrintDelay;
    uint32_t PreviousPrintTime; 

    public:
    SerialPrinter(
      HardwareSerial *printerSerial,
      std::function<String(void)> getSerialStringCallback,
      int printDelay
    );
    void SerialPrintln();
  };

#endif
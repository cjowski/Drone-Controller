#ifndef SERIAL_PRINT_CONTROLLER_H
#define SERIAL_PRINT_CONTROLLER_H

  #include "Serial\Printer\SerialPrinter.h"

  class SerialPrintController
  {
    public:
    SerialPrintController(
      HardwareSerial *printerSerial,
      int serialBaudRate,
      std::function<std::list<String>(void)> getFmStrings,
      std::function<std::list<String>(void)> getGyroStrings
    );
    void Print();

    private:
    const int FM_PRINT_KEY = 'F';
    const int GYRO_PRINT_KEY = 'G';
    const int FM_PRINT_DELAY = 50;
    const int GYRO_PRINT_DELAY = 120;

    HardwareSerial *PrinterSerial;
    int SerialBaudRate;
    SerialPrinter *SerialPrinterFm;
    SerialPrinter *SerialPrinterGyro;
  };

#endif
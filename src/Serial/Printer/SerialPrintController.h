#ifndef PRINT_CONTROLLER_H
#define PRINT_CONTROLLER_H

  #include <functional>
  #include <wiring_time.h>
  #include "SerialPrinter.h"

  class SerialPrintController
  {
    private:
    SerialPrinter *MySerialPrinter;
    uint32_t PrintDelay;
    std::function<SerialValue*(void)> GetSerialValue;
    uint32_t PreviousPrintTime = 0;

    public:
    SerialPrintController(
      SerialPrinter *mySerialPrinter,
      int printDelay,
      std::function<SerialValue*(void)> getSerialValue
    );
    void Loop();
  };

#endif
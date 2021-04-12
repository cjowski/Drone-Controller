#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H
  
  #include "Serial/Printer/SerialPrintController.h"
  #include "Serial/Reader/SerialReader.h"
  #include "Task/TaskController/TaskController.h"
  #include "Task/UndefinedSerialTask.h"
  #include "DroneController/Task/SayHiToEsp/SayHiToEspTask.h"

  #define HAVE_HWSERIAL1

  #define SERIAL1_TX_PIN PA9
  #define SERIAL1_RX_PIN PA10

  #define SERIAL3_TX_PIN PC10
  #define SERIAL3_RX_PIN PC11

  #define SERIAL_BAUD_RATE 19200

  class SerialController
  {
    private:
    std::list<SerialPrintController*> MySerialPrintControllers;
    SerialPrinter *MySerialPrinter;
    SerialReader *MySerialReader;
    TaskController *MyTaskController;

    void ProcessSerialValue(UndefinedSerialValue serialValue);
    void ProcessSerialValueTask(UndefinedSerialTask serialTask);

    public:
    SerialController(
      std::function<SerialValue*(void)> getFmSerialValue,
      std::function<SerialValue*(void)> getGyroSerialValue,
      TaskController *myTaskController
    );
    void Loop();
  };

#endif
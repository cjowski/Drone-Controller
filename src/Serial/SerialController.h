#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H
  
  #include "Board/BoardSerial.h"
  #include "Serial/Printer/SerialPrintController.h"
  #include "Serial/Reader/SerialReader.h"
  #include "Task/TaskController/TaskController.h"
  #include "Task/UndefinedSerialTask.h"
  #include "DroneController/Task/SayHiToEsp/SayHiToEspTask.h"

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
      const BoardSerial *espCommunicationSerial,
      std::function<SerialValue*(void)> getFmSerialValue,
      std::function<SerialValue*(void)> getGyroSerialValue,
      std::function<SerialValue*(void)> getMotorsSerialValue,
      TaskController *myTaskController
    );
    void Loop();
  };

#endif
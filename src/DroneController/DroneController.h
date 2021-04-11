#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

  #include "Fm/FmController.h"
  #include "Gyro/GyroController.h"
  #include "Serial/Printer/SerialPrintController.h"
  #include "Serial/Reader/SerialReader.h"
  #include "Task/TaskController/TaskController.h"
  #include "Task/UndefinedSerialTask.h"
  #include "Task/SayHiToEsp/SayHiToEspTask.h"

  #define HAVE_HWSERIAL1

  #define SERIAL1_TX_PIN PA9
  #define SERIAL1_RX_PIN PA10

  #define SERIAL3_TX_PIN PC10
  #define SERIAL3_RX_PIN PC11

  #define SERIAL_BAUD_RATE 19200

  class DroneController
  {
    private:
    FmController *MyFmController;
    GyroController *MyGyroController;
    std::list<SerialPrintController*> MySerialPrintControllers;
    SerialPrinter *MySerialPrinter;
    SerialReader *MySerialReader;
    TaskController *MyTaskController;

    public:
    DroneController();
    void Loop();
    void ProcessSerialValue(UndefinedSerialValue serialValue);
    void ProcessSerialValueTask(UndefinedSerialTask serialTask);
  };

#endif
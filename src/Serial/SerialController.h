#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H
  
  #include "Board/BoardSerial.h"
  #include "Serial/Print/SerialPeriodicalPrinter.h"
  #include "Serial/Read/SerialReader.h"
  #include "Serial/Type/StringList/Encoder/StringListEncoder.h"
  #include "Serial/Type/StringList/Decoder/StringListDecoder.h"
  #include "Task/TaskController/TaskController.h"
  #include "Task/UndefinedSerialTask.h"
  #include "Task/Type/SayHiToEsp/SayHiToEspTask.h"

  #define SERIAL_BAUD_RATE 19200

  class SerialController
  {
    private:
    std::list<SerialPeriodicalPrinter*> PeriodicalPrinters;
    SerialPrinter *Printer;
    SerialReader *Reader;
    TaskController *MyTaskController;

    // void ProcessSerialValue(UndefinedSerialValue serialValue);
    // void ProcessSerialValueTask(UndefinedSerialTask serialTask);

    public:
    SerialController(
      const BoardSerial *espCommunicationSerial,
      std::function<SerialEncoderInput*(void)> getFmSerialEncoderInput,
      std::function<SerialEncoderInput*(void)> getGyroSerialEncoderInput,
      std::function<SerialEncoderInput*(void)> getMotorsSerialEncoderInput,
      TaskController *myTaskController
    );
    void Loop();
  };

#endif
#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H
  
  #include "Board/BoardSerial.h"
  #include "Serial/Print/SerialPeriodicalPrinter.h"
  #include "Serial/Read/SerialReader.h"
  #include "Serial/Type/StringList/Encoder/StringListEncoder.h"
  #include "Serial/Type/StringList/Decoder/StringListDecoder.h"
  #include "Task/TaskController/TaskController.h"

  #define SERIAL_BAUD_RATE 19200

  class SerialController
  {
    private:
    SerialPrinter *Printer;
    SerialReader *Reader;
    std::list<SerialPeriodicalPrinter*> PeriodicalPrinters;
    TaskController *MyTaskController;

    void ProcessDecoderOutput(SerialDecoderOutput *decoderOutput);

    public:
    SerialController(
      SerialPrinter *printer,
      SerialReader *reader,
      std::function<SerialEncoderInput*(void)> getFmSerialEncoderInput,
      std::function<SerialEncoderInput*(void)> getGyroSerialEncoderInput,
      std::function<SerialEncoderInput*(void)> getMotorsSerialEncoderInput,
      TaskController *myTaskController
    );
    void Loop();
  };

#endif
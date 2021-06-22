#include "SerialController.h"

SerialController::SerialController(
  SerialPrinter *printer,
  SerialReader *reader,
  std::function<SerialEncoderInput*(void)> getFmSerialEncoderInput,
  std::function<SerialEncoderInput*(void)> getGyroSerialEncoderInput,
  std::function<SerialEncoderInput*(void)> getMotorsSerialEncoderInput,
  TaskController *myTaskController
)
{
  Printer = printer;
  Reader = reader;

  PeriodicalPrinters.push_back(
    new SerialPeriodicalPrinter(
      Printer,
      50,
      getFmSerialEncoderInput,
      false
    )
  );

  PeriodicalPrinters.push_back(
    new SerialPeriodicalPrinter(
      Printer,
      120,
      getGyroSerialEncoderInput,
      false
    )
  );

  PeriodicalPrinters.push_back(
    new SerialPeriodicalPrinter(
      Printer,
      120,
      getMotorsSerialEncoderInput,
      false
    )
  );
  
  MyTaskController = myTaskController;
}

void SerialController::Loop()
{
  for (auto it = PeriodicalPrinters.begin(); it != PeriodicalPrinters.end(); it++)
  {
    (*it)->Loop();
  }

  SerialDecoderOutput *decoderOutput = Reader->Read();
  ProcessDecoderOutput(decoderOutput);
  delete decoderOutput;
}

void SerialController::ProcessDecoderOutput(SerialDecoderOutput *decoderOutput)
{
  if (!decoderOutput->Exists)
  {
    return;
  }
  if (UndefinedSerialTask::SerialDecoderOutputMatched(decoderOutput))
  {
    MyTaskController->ProcessUndefinedSerialTask(
      UndefinedSerialTask(decoderOutput)
    );
    return;
  }
}
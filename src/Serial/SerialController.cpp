#include "SerialController.h"

SerialController::SerialController(
  const BoardSerial *espCommunicationSerial,
  std::function<SerialEncoderInput*(void)> getFmSerialEncoderInput,
  std::function<SerialEncoderInput*(void)> getGyroSerialEncoderInput,
  std::function<SerialEncoderInput*(void)> getMotorsSerialEncoderInput,
  TaskController *myTaskController
)
{
  HardwareSerial* stmEspSerial = new HardwareSerial(
    espCommunicationSerial->RX_PIN(),
    espCommunicationSerial->TX_PIN()
  );
  Printer = new SerialPrinter(
    new StringListEncoder(false),
    stmEspSerial,
    SERIAL_BAUD_RATE
  );

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

  Reader = new SerialReader(
    new StringListDecoder(true),
    stmEspSerial,
    SERIAL_BAUD_RATE
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
    ProcessUndefinedSerialTask(
      UndefinedSerialTask(decoderOutput)
    );
    return;
  }
}

void SerialController::ProcessUndefinedSerialTask(UndefinedSerialTask undefinedSerialTask)
{
  if (!MyTaskController->EspTaskProcessed(undefinedSerialTask.GetTaskID()))
  {
    if (undefinedSerialTask.GetTaskType() == StmTask::SayHiToStm)
    {
      MyTaskController->AddTask(
        new SayHiToEspTask(
          MyTaskController->GetNewTaskID(),
          undefinedSerialTask.GetTaskID(),
          millis(),
          Printer,
          true
        )
      );
      MyTaskController->AddProcessedEspTaskID(undefinedSerialTask.GetTaskID());
    }
  }
}
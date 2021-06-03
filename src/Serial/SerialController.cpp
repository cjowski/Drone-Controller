#include "SerialController.h"

SerialController::SerialController(
  const BoardSerial *espCommunicationSerial,
  std::function<SerialValue*(void)> getFmSerialValue,
  std::function<SerialValue*(void)> getGyroSerialValue,
  std::function<SerialValue*(void)> getMotorsSerialValue,
  TaskController *myTaskController
)
{
  HardwareSerial* stmEspSerial = new HardwareSerial(
    espCommunicationSerial->RX_PIN(),
    espCommunicationSerial->TX_PIN()
  );
  MySerialPrinter = new SerialPrinter(stmEspSerial, SERIAL_BAUD_RATE);

  MySerialPrintControllers.push_back(
    new SerialPrintController(
      MySerialPrinter,
      50,
      getFmSerialValue
    )
  );

  MySerialPrintControllers.push_back(
    new SerialPrintController(
      MySerialPrinter,
      120,
      getGyroSerialValue
    )
  );

  MySerialPrintControllers.push_back(
    new SerialPrintController(
      MySerialPrinter,
      120,
      getMotorsSerialValue
    )
  );

  MySerialReader = new SerialReader(stmEspSerial);
  MyTaskController = myTaskController;
}

void SerialController::Loop()
{
  for (auto it = MySerialPrintControllers.begin(); it != MySerialPrintControllers.end(); it++)
  {
    (*it)->Loop();
  }
  ProcessSerialValue(
    MySerialReader->Read()
  );
}

void SerialController::ProcessSerialValue(UndefinedSerialValue serialValue)
{
  if (!serialValue.Exists())
  {
    return;
  }

  char readValueKey = serialValue.GetReadValueKey();
  std::list<String> serialValues = serialValue.GetPrintStrings();
  if (UndefinedSerialTask().SerialValueValid(readValueKey, serialValues))
  {
    ProcessSerialValueTask(
      UndefinedSerialTask(serialValues)
    );
    return;
  }
}

void SerialController::ProcessSerialValueTask(UndefinedSerialTask serialTask)
{
  if (!MyTaskController->EspTaskProcessed(serialTask.GetTaskID()))
  {
    if (serialTask.GetTaskType() == StmTask::SayHiToStm)
    {
      MyTaskController->AddTask(
        new SayHiToEspTask(
          MyTaskController->GetNewTaskID(),
          serialTask.GetTaskID(),
          millis(),
          MySerialPrinter
        )
      );
      MyTaskController->AddProcessedEspTaskID(serialTask.GetTaskID());
    }
  }
}
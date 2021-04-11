#include "DroneController.h"

DroneController::DroneController()
{
  MyFmController = new FmController();
  MyGyroController = new GyroController();
  HardwareSerial* stmEspSerial = new HardwareSerial(SERIAL3_RX_PIN, SERIAL3_TX_PIN);
  MySerialPrinter = new SerialPrinter(stmEspSerial, SERIAL_BAUD_RATE);

  MySerialPrintControllers.push_back(
    new SerialPrintController(
      MySerialPrinter,
      50,
      [&] () -> SerialValue* {
        return MyFmController->GetSerialValue();
      }
    )
  );

  MySerialPrintControllers.push_back(
    new SerialPrintController(
      MySerialPrinter,
      120,
      [&] () -> SerialValue* {
        return MyGyroController->GetSerialValue();
      }
    )
  );

  MySerialReader = new SerialReader(stmEspSerial);
  MyTaskController = new TaskController();
}

void DroneController::Loop()
{
  MyFmController->Loop();
  MyGyroController->Loop();
  for (auto it = MySerialPrintControllers.begin(); it != MySerialPrintControllers.end(); it++)
  {
    (*it)->Loop();
  }
  ProcessSerialValue(
    MySerialReader->Read()
  );
  MyTaskController->Loop();
}

void DroneController::ProcessSerialValue(UndefinedSerialValue serialValue)
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

void DroneController::ProcessSerialValueTask(UndefinedSerialTask serialTask)
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
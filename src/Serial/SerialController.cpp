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
    new StringListDecoder(false),
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
  // ProcessSerialValue(
  //   Reader->Read()
  // );
}

// void SerialController::ProcessSerialValue(UndefinedSerialValue serialValue)
// {
//   if (!serialValue.Exists())
//   {
//     return;
//   }

//   char readValueKey = serialValue.GetReadValueKey();
//   std::list<String> serialValues = serialValue.GetPrintStrings();
//   if (UndefinedSerialTask().SerialValueValid(readValueKey, serialValues))
//   {
//     ProcessSerialValueTask(
//       UndefinedSerialTask(serialValues)
//     );
//     return;
//   }
// }

// void SerialController::ProcessSerialValueTask(UndefinedSerialTask serialTask)
// {
//   if (!MyTaskController->EspTaskProcessed(serialTask.GetTaskID()))
//   {
//     if (serialTask.GetTaskType() == StmTask::SayHiToStm)
//     {
//       MyTaskController->AddTask(
//         new SayHiToEspTask(
//           MyTaskController->GetNewTaskID(),
//           serialTask.GetTaskID(),
//           millis(),
//           MySerialPrinter
//         )
//       );
//       MyTaskController->AddProcessedEspTaskID(serialTask.GetTaskID());
//     }
//   }
// }
#include "SayHiToEspMessage.h"

SayHiToEspMessage::SayHiToEspMessage(int taskID, int espTaskID, String greeting)
{
  TaskID = taskID;
  EspTaskID = espTaskID;
  Greeting = greeting;
}

SerialEncoderInput *SayHiToEspMessage::GetSerialEncoderInput()
{
  std::list<String> texts;
  texts.push_back(String(TaskID));
  texts.push_back(String(StmTask::SayHiToEsp));
  texts.push_back(String(EspTaskID));
  texts.push_back(Greeting);
  return new StringListEncoderInput(
    StmTask::SERIAL_KEY,
    texts
  );
}

String SayHiToEspMessage::ToString()
{
  return "STM32 taskID: " + String(TaskID)
    + ", ESP taskID: " + String(EspTaskID)
    + ", Type: " + String(StmTask::SayHiToEsp)
    + ", Greeting: " + Greeting;
}
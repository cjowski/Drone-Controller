#include "SayHiToEspMessage.h"

SayHiToEspMessage::SayHiToEspMessage(int taskID, int espTaskID, String greeting)
{
  TaskID = taskID;
  EspTaskID = espTaskID;
  Greeting = greeting;
}

std::list<String> SayHiToEspMessage::GetPrintStrings()
{
  std::list<String> printStrings;
  printStrings.push_back(String(TaskID));
  printStrings.push_back(String(StmTask::SayHiToEsp));
  printStrings.push_back(String(EspTaskID));
  printStrings.push_back(Greeting);
  return printStrings;
}
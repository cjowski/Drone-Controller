#include "SayHiToEspTask.h"

SayHiToEspTask::SayHiToEspTask(
  int id,
  int espTaskID,
  int startTime,
  SerialPrinter *serialPrinter,
  bool debugMode
)
{
  ID = id;
  EspTaskID = espTaskID;
  StartTime = startTime;
  PreviousStepTime = startTime;
  Printer = serialPrinter;
  DebugMode = debugMode;
}

void SayHiToEspTask::Loop()
{
  if (!IsGreetingChosen)
  {
    ChosenGreeting = ChooseGreeting();
    IsGreetingChosen = true;
  }
  SayHiToEspMessage *message = new SayHiToEspMessage(ID, EspTaskID, ChosenGreeting);
  if (DebugMode) Serial.println(message->ToString());
  Printer->Println(message->GetSerialEncoderInput());
  delete message;
}

String SayHiToEspTask::ChooseGreeting()
{
  std::srand(millis());
  int randomIndex = std::rand()/((RAND_MAX + 1u)/POSSIBLE_GREETINGS_COUNT);
  return POSSIBLE_GREETINGS[randomIndex];
}
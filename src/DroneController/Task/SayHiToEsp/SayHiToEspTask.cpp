#include "SayHiToEspTask.h"

SayHiToEspTask::SayHiToEspTask(
  int id,
  int espTaskID,
  int startTime,
  SerialPrinter *serialPrinter
)
{
  ID = id;
  EspTaskID = espTaskID;
  StartTime = startTime;
  PreviousStepTime = startTime;
  Printer = serialPrinter;
}

void SayHiToEspTask::Loop()
{
  if (!IsGreetingChosen)
  {
    ChosenGreeting = ChooseGreeting();
    IsGreetingChosen = true;
  }
  SayHiToEspMessage *message = new SayHiToEspMessage(ID, EspTaskID, ChosenGreeting);
  Serial.println(message->ToSerialString());
  Printer->Println(message);
  delete message;
}

String SayHiToEspTask::ChooseGreeting()
{
  std::srand(millis());
  int randomIndex = std::rand()/((RAND_MAX + 1u)/POSSIBLE_GREETINGS_COUNT);
  return POSSIBLE_GREETINGS[randomIndex];
}
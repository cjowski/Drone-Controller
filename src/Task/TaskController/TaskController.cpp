#include "TaskController.h"

TaskController::TaskController(SerialPrinter *printer, bool debugMode)
{
  Printer = printer;
  DebugMode = debugMode;
}

int TaskController::GetNewTaskID()
{
  return NextTaskID++;
}

void TaskController::AddTask(StmTask *newTask)
{
  Tasks.push_back(newTask);
}

void TaskController::AddProcessedEspTaskID(int espTaskID)
{
  ProcessedEspTaskIDs.push_back(espTaskID);
}

bool TaskController::EspTaskProcessed(int espTaskID)
{
  return std::find(
    ProcessedEspTaskIDs.begin(),
    ProcessedEspTaskIDs.end(),
    espTaskID
  ) != ProcessedEspTaskIDs.end();
}

void TaskController::ProcessUndefinedSerialTask(UndefinedSerialTask undefinedSerialTask)
{
  if (!EspTaskProcessed(undefinedSerialTask.GetTaskID()))
  {
    if (undefinedSerialTask.GetTaskType() == StmTask::SayHiToStm)
    {
      AddTask(
        new SayHiToEspTask(
          GetNewTaskID(),
          undefinedSerialTask.GetTaskID(),
          millis(),
          Printer,
          true
        )
      );
      AddProcessedEspTaskID(undefinedSerialTask.GetTaskID());
    }
  }
}

void TaskController::Loop()
{
  int currentTime = millis();
  KillDoneOrOvertimeTasks(currentTime);
  for (auto it = Tasks.begin(); it != Tasks.end(); it++)
  {
    if ((*it)->IsReadyForLoop(currentTime))
    {
      (*it)->Loop();
      (*it)->PreviousStepTime = currentTime;
    }
  }
}

void TaskController::KillDoneOrOvertimeTasks(int currentTime)
{
  int currentTaskIndex = 0;
  std::list<int> deadTaskIndexes;
  for (auto it = Tasks.begin(); it != Tasks.end(); it++, currentTaskIndex++)
  {
    if ((*it)->Done || (*it)->IsOvertime(currentTime))
    {
      delete *it;
      deadTaskIndexes.push_back(currentTaskIndex);
    }
  }

  std::list<StmTask*>::iterator taskIterator;
  for (auto it = deadTaskIndexes.begin(); it != deadTaskIndexes.end(); it++)
  {
    taskIterator = Tasks.begin();
    advance(taskIterator, *it);
    Tasks.erase(taskIterator);
  }
}
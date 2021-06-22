#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

  #include <list>
  #include <algorithm>
  #include <wiring_time.h>
  #include <Serial/Print/SerialPrinter.h>
  #include "Task/StmTask.h"
  #include "Task/Type/SayHiToEsp/SayHiToEspTask.h"
  #include "Task/UndefinedSerialTask.h"

  class TaskController
  {
    private:
    std::list<StmTask*> Tasks;
    SerialPrinter *Printer;
    void KillDoneOrOvertimeTasks(int currentTime);
    std::list<int> ProcessedEspTaskIDs;
    int NextTaskID = 1;
    bool DebugMode = false;

    public:
    TaskController(SerialPrinter *printer, bool debugMode);
    int GetNewTaskID();
    void AddTask(StmTask *newTask);
    void AddProcessedEspTaskID(int espTaskID);
    bool EspTaskProcessed(int espTaskID);
    void ProcessUndefinedSerialTask(UndefinedSerialTask undefinedSerialTask);
    void Loop();
  };

#endif
#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

  #include <list>
  #include <algorithm>
  #include <wiring_time.h>
  #include "Task/StmTask.h"

  class TaskController
  {
    private:
    std::list<StmTask*> Tasks;
    void KillDoneOrOvertimeTasks(int currentTime);
    std::list<int> ProcessedEspTaskIDs;
    int NextTaskID = 1;

    public:
    TaskController();
    int GetNewTaskID();
    void AddTask(StmTask *newTask);
    void AddProcessedEspTaskID(int espTaskID);
    bool EspTaskProcessed(int espTaskID);
    void Loop();
  };

#endif
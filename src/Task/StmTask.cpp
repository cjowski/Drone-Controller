#include "StmTask.h"

StmTask::StmTask(int id)
{
  ID = id;
}

bool StmTask::IsReadyForLoop(int currentTime)
{
  return currentTime - PreviousStepTime > LOOP_STEP_DELAY_TIME();
}

bool StmTask::IsOvertime(int currentTime)
{
  return currentTime - StartTime > LIFE_TIME();
}
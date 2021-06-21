#ifndef STM_TASK_H
#define STM_TASK_H

  class StmTask
  {
    public:
    enum StmTaskType
    {
      SayHiToEsp
    };
    enum EspTaskType
    {
      SayHiToStm
    };

    StmTask() { };
    StmTask(int id);
    virtual ~StmTask() { };
    int ID = -1;
    bool Done = false;
    int StartTime = 0;
    int PreviousStepTime = 0;
    static const char SERIAL_KEY = 'T';

    virtual StmTaskType TYPE() const = 0;
    virtual int LIFE_TIME() const = 0;
    virtual int LOOP_STEP_DELAY_TIME() const = 0;
    virtual void Loop() = 0;
    bool IsReadyForLoop(int currentTime);
    bool IsOvertime(int currentTime);
  };

#endif
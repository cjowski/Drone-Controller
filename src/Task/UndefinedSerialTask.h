#ifndef UNDEFINED_SERIAL_TASK_H
#define UNDEFINED_SERIAL_TASK_H

  #include "Task/StmTask.h"
  #include "Serial/Value/SerialValue.h"

  class UndefinedSerialTask : public SerialValue
  {
    private:
    int TaskID;
    int TaskType;
    std::list<String> OtherSerialValues;
    static bool IsInteger(String text);
    const unsigned int MIN_SERIAL_VALUE_COUNT = 2;

    protected:
    bool SerialValuesMatched(std::list<String> serialValues);

    public:
    UndefinedSerialTask() { };
    UndefinedSerialTask(std::list<String> serialValues);
    int SERIAL_VALUES_COUNT() const { return -1; };
    char SERIAL_VALUE_KEY() const { return StmTask::SERIAL_VALUE_KEY; };
    int GetTaskID();
    int GetTaskType();
    std::list<String> GetOtherSerialValues();
    std::list<String> GetPrintStrings();
  };

#endif
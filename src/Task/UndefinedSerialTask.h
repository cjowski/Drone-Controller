#ifndef UNDEFINED_SERIAL_TASK_H
#define UNDEFINED_SERIAL_TASK_H

  #include "Task/StmTask.h"
  #include <Serial/Type/StringList/Decoder/StringListDecoderOutput.h>

  class UndefinedSerialTask
  {
    private:
    int TaskID;
    int TaskType;
    std::list<String> OtherSerialValues;
    static bool IsInteger(String text);
    static const unsigned int MIN_SERIAL_VALUE_COUNT = 2;

    public:
    UndefinedSerialTask(SerialDecoderOutput *decoderOutput) : UndefinedSerialTask((StringListDecoderOutput*) decoderOutput) { };
    UndefinedSerialTask(StringListDecoderOutput *decoderOutput);
    static bool SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput);
    int GetTaskID();
    int GetTaskType();
    std::list<String> GetOtherSerialValues();
    std::list<String> GetPrintStrings();
  };

#endif
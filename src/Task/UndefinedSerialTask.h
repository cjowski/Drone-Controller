#ifndef UNDEFINED_SERIAL_TASK_H
#define UNDEFINED_SERIAL_TASK_H

  #include <Serial/Type/StringList/Decoder/StringListDecoderOutput.h>
  #include "Task/StmTask.h"

  class UndefinedSerialTask
  {
    private:
    static const unsigned int MIN_SERIAL_TEXTS_COUNT = 2;

    int TaskID;
    int TaskType;
    std::list<String> OtherSerialTexts;
    static bool IsInteger(String text);

    public:
    UndefinedSerialTask(SerialDecoderOutput *decoderOutput) : UndefinedSerialTask((StringListDecoderOutput*) decoderOutput) { };
    UndefinedSerialTask(StringListDecoderOutput *decoderOutput);
    static bool SerialDecoderOutputMatched(SerialDecoderOutput *decoderOutput);
    int GetTaskID();
    int GetTaskType();
  };

#endif
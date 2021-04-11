#ifndef SAY_HI_TO_ESP_MESSAGE_H
#define SAY_HI_TO_ESP_MESSAGE_H

  #include "Task/StmTask.h"
  #include "Serial/Value/SerialValue.h"

  class SayHiToEspMessage : public SerialValue
  {
    private:
    int TaskID;
    String Greeting;
    int EspTaskID;

    protected:
    bool SerialValuesMatched(std::list<String> serialValues) { return false; };

    public:
    SayHiToEspMessage(int taskID, int espTaskID, String greeting);
    int SERIAL_VALUES_COUNT() const { return 2; };
    char SERIAL_VALUE_KEY() const { return StmTask::SERIAL_VALUE_KEY; };
    std::list<String> GetPrintStrings();
  };

#endif
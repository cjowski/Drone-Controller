#ifndef SAY_HI_TO_ESP_MESSAGE_H
#define SAY_HI_TO_ESP_MESSAGE_H

  #include "Task/StmTask.h"
  #include <Serial/Type/StringList/Encoder/StringListEncoderInput.h>

  class SayHiToEspMessage
  {
    private:
    int TaskID;
    String Greeting;
    int EspTaskID;

    public:
    SayHiToEspMessage(int taskID, int espTaskID, String greeting);
    SerialEncoderInput *GetSerialEncoderInput();
    String ToString();
  };

#endif
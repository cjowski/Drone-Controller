#ifndef SAY_HI_TO_ESP_TASK_H
#define SAY_HI_TO_ESP_TASK_H

  #include <WSerial.h>
  #include <wiring_time.h>
  #include <Serial/Print/SerialPrinter.h>
  #include "Task/StmTask.h"
  #include "SayHiToEspMessage.h"

  class SayHiToEspTask : public StmTask
  {
    private:
    int EspTaskID;
    String ChosenGreeting = "";
    bool IsGreetingChosen = false;
    SerialPrinter *Printer;
    bool DebugMode;
    static const int POSSIBLE_GREETINGS_COUNT = 15;
    String POSSIBLE_GREETINGS[POSSIBLE_GREETINGS_COUNT] = {
      "HELLO",
      "SALUT",
      "ZDRAVSTVUYTE",
      "CIAO",
      "OI",
      "ASALAAM ALAIKUM",
      "ANYOUNG HASEYO",
      "GOEDENDAG",
      "YASSOU",
      "TJENA",
      "SELAM",
      "SIEMA",
      "SHALOM",
      "NAMASTE",
      "SHIKAMOO"
    };

    public:
    StmTaskType TYPE() const { return StmTask::SayHiToEsp; };
    int LIFE_TIME() const { return 1200; };
    int LOOP_STEP_DELAY_TIME() const { return 250; };

    SayHiToEspTask(
      int id,
      int espTaskID,
      int startTime,
      SerialPrinter *serialPrinter,
      bool debugMode
    );
    void Loop();
    String ChooseGreeting();
  };

#endif
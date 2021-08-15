#ifndef BLUE_PILL_SETUP_H
#define BLUE_PILL_SETUP_H

  #include "Board/BoardSetup.h"
  #include "Serial/BluePillSerial1.h"
  #include "Serial/BluePillSerial3.h"
  #include "Timer/BluePillTimer1.h"
  #include "Timer/BluePillTimer2.h"

  class BluePillSetup : public BoardSetup
  {
    public:
    BluePillSetup()
    {
      EspCommunicationSerial = new BluePillSerial1();
      FmBoardTimerSetup = new BoardTimerSetup(
        new BluePillTimer2()
      );
      MotorBoardTimer = new BluePillTimer1();
    }
  };

#endif
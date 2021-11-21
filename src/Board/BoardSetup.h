#ifndef BOARD_SETUP_H
#define BOARD_SETUP_H

  #include "BoardSerial.h"
  #include "BoardTimer/BoardTimerSetup.h"
  #include "Button/Button.h"

  //todo convert to abstract class
  class BoardSetup
  {
    public:
    const BoardSerial *EspCommunicationSerial;
    const BoardTimerSetup *FmBoardTimerSetup;
    const BoardTimerSetup *MotorBoardTimerSetup;
    Button *MotorOnOffButton; 
  };

#endif
#ifndef BLACK_PILL_SETUP_H
#define BLACK_PILL_SETUP_H

  #include "Board/BoardSetup.h"
  #include "Serial/BlackPillSerial1.h"
  #include "Timer/BlackPillTimer1.h"
  #include "Timer/BlackPillTimer2.h"
  #include "Timer/BlackPillTimer3.h"
  #include "Timer/BlackPillTimer4.h"

  class BlackPillSetup : public BoardSetup
  {
    public:
    BlackPillSetup()
    {
      EspCommunicationSerial = new BlackPillSerial1();
      FmBoardTimerSetup = new BoardTimerSetup(
        new BlackPillTimer3()
      );

      auto timer2 = new BlackPillTimer2();
      auto timer4 = new BlackPillTimer4();

      std::list<BoardTimerChannelSetup*> motorChannels;
      motorChannels.push_back(new BoardTimerChannelSetup(1, timer2));
      motorChannels.push_back(new BoardTimerChannelSetup(2, timer2));
      motorChannels.push_back(new BoardTimerChannelSetup(3, timer2));
      motorChannels.push_back(new BoardTimerChannelSetup(4, timer4));

      MotorBoardTimerSetup = new BoardTimerSetup(
        motorChannels
      );

      MotorOnOffButton = new Button(PA15);
    }
  };

#endif
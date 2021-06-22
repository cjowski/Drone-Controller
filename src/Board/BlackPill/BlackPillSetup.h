#ifndef BLACK_PILL_SETUP_H
#define BLACK_PILL_SETUP_H

  #include "Board/BoardSetup.h"
  #include "Serial/BlackPillSerial1.h"
  #include "Timer/BlackPillTimer1.h"
  #include "Timer/BlackPillTimer2.h"
  #include "Timer/BlackPillTimer3.h"

  class BlackPillSetup : public BoardSetup
  {
    public:
    const BoardSerial *ESP_COMMUNICATION_SERIAL() const {
      return new BlackPillSerial1();
    };
    const BoardTimer *FM_BOARD_TIMER() const {
      return new BlackPillTimer2();
    };
    const BoardTimer *MOTOR_BOARD_TIMER() const {
      return new BlackPillTimer3();
    };
  };

#endif
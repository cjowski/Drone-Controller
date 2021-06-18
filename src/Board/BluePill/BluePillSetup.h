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
    const BoardSerial *ESP_COMMUNICATION_SERIAL() const {
      return new BluePillSerial1();
    };
    const BoardTimer *FM_BOARD_TIMER() const {
      return new BluePillTimer2();
    };
    const BoardTimer *MOTOR_BOARD_TIMER() const {
      return new BluePillTimer1();
    };
  };

#endif
#ifndef BOARD_SETUP_H
#define BOARD_SETUP_H

  #include "BoardSerial.h"
  #include "BoardTimer.h"

  class BoardSetup
  {
    public:
    virtual const BoardSerial *ESP_COMMUNICATION_SERIAL() const = 0;
    virtual const BoardTimer *FM_BOARD_TIMER() const = 0;
    virtual const BoardTimer *MOTOR_BOARD_TIMER() const = 0;
  };

#endif
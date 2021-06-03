#ifndef NUCLEO_L476RG_SETUP_H
#define NUCLEO_L476RG_SETUP_H

  #include "Board/BoardSetup.h"
  #include "Serial/NucleoL476rgSerial1.h"
  #include "Serial/NucleoL476rgSerial3.h"
  #include "Timer/NucleoL476rgTimer1.h"
  #include "Timer/NucleoL476rgTimer2.h"
  #include "Timer/NucleoL476rgTimer3.h"

  class NucleoL476rgSetup : public BoardSetup
  {
    public:
    const BoardSerial *ESP_COMMUNICATION_SERIAL() const {
      return new NucleoL476rgSerial3();
    };
    const BoardTimer *FM_BOARD_TIMER() const {
      return new NucleoL476rgTimer2();
    };
    const BoardTimer *MOTOR_BOARD_TIMER() const {
      return new NucleoL476rgTimer1();
    };
  };

#endif
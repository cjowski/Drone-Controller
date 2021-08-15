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
    NucleoL476rgSetup()
    {
      EspCommunicationSerial = new NucleoL476rgSerial3();
      FmBoardTimerSetup = new BoardTimerSetup(
        new NucleoL476rgTimer2()
      );
      MotorBoardTimer = new NucleoL476rgTimer1();
    }
  };

#endif
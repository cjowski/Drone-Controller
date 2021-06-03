#ifndef NUCLEO_L476RG_SERIAL_1_H
#define NUCLEO_L476RG_SERIAL_1_H

  #include "Board/BoardSerial.h"

  class NucleoL476rgSerial1 : public BoardSerial
  {
    public:
    const int RX_PIN() const {
      return PA10;
    };
    const int TX_PIN() const {
      return PA9;
    };
  };

#endif
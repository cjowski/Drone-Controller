#ifndef NUCLEO_L476RG_SERIAL_3_H
#define NUCLEO_L476RG_SERIAL_3_H

  #include "Board/BoardSerial.h"

  class NucleoL476rgSerial3 : public BoardSerial
  {
    public:
    const int RX_PIN() const {
      return PC11;
    };
    const int TX_PIN() const {
      return PC10;
    };
  };

#endif
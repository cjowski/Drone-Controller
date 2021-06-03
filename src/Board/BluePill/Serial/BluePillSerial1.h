#ifndef BLUE_PILL_SERIAL_1_H
#define BLUE_PILL_SERIAL_1_H

  #include "Board/BoardSerial.h"

  class BluePillSerial1 : public BoardSerial
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
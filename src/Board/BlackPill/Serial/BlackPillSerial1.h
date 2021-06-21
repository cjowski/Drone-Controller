#ifndef BLACK_PILL_SERIAL_1_H
#define BLACK_PILL_SERIAL_1_H

  #include "Board/BoardSerial.h"

  class BlackPillSerial1 : public BoardSerial
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
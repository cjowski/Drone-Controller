#ifndef BLUE_PILL_SERIAL_3_H
#define BLUE_PILL_SERIAL_3_H

  #include "Board/BoardSerial.h"

  class BluePillSerial3 : public BoardSerial
  {
    public:
    const int RX_PIN() const {
      return PB11;
    };
    const int TX_PIN() const {
      return PB10;
    };
  };

#endif
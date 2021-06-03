#ifndef BOARD_SERIAL_H
#define BOARD_SERIAL_H

  class BoardSerial
  {
    public:
    virtual const int RX_PIN() const = 0;
    virtual const int TX_PIN() const = 0;
  };

#endif
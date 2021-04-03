#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

  #include "Serial/Printer/SerialPrintController.h"
  #include "Serial/Reader/Read/String/SerialStringReader.h"
  #include "Fm/FmController.h"
  #include "Gyro/GyroController.h"

  #define HAVE_HWSERIAL1

  #define SERIAL1_TX_PIN PA9
  #define SERIAL1_RX_PIN PA10

  #define SERIAL3_TX_PIN PC10
  #define SERIAL3_RX_PIN PC11

  #define SERIAL_BAUD_RATE 19200

  class DroneController
  {
    private:
    FmController *MyFmController;
    GyroController *MyGyroController;
    SerialPrintController *MySerialPrintController;
    SerialReader *MySerialReader;

    public:
    DroneController();
    void Loop();
  };

#endif
#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

  #include "Fm/FmController.h"
  #include "Gyro/GyroController.h"
  #include "Serial/Printer/SerialPrintController.h"
  #include "Serial/Reader/SerialReader.h"

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
    std::list<SerialPrintController*> MySerialPrintControllers;
    SerialReader *MySerialReader;

    public:
    DroneController();
    void Loop();
  };

#endif
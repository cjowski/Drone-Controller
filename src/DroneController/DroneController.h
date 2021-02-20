#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

  #include "Fm\TimerController\Timer2.h"
  #include "Fm\FmChannels\FmChannelsContainer.h"
  #include "Gyro\Gyro.h"
  #include "Gyro\GyroAngles.h"
  #include "SerialPrint\SerialPrinter.h"

  #define HAVE_HWSERIAL1

  #define SERIAL1_TX_PIN PA9
  #define SERIAL1_RX_PIN PA10

  #define SERIAL3_TX_PIN PC10
  #define SERIAL3_RX_PIN PC11

  #define SERIAL_BAUD_RATE 19200

  #define CHANNELS_COUNT 4

  class DroneController
  {
    private:
    HardwareTimer HardwareTimer2 = HardwareTimer(TIM2);
    TimerController *MyTimerController;
    FmChannelsContainer *MyFmChannelsContainer;

    Gyro *MyGyro;
    GyroAngles *MyGyroAngles;

    HardwareSerial *PrinterSerial;
    SerialPrinter *SerialPrinterFm;
    SerialPrinter *SerialPrinterGyro;

    void SetupTimers();
    void SetupFmChannelsContainer();
    void SetupGyro();
    void SetupSerials();
    void SetupSerialPrinters();

    void UpdateFmChannelsState();
    void UpdateGyroState();

    public:
    DroneController();
    void Setup();
    void Loop();
    void SerialPrint();
  };

#endif
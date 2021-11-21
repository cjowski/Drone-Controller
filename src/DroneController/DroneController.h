#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

  #include "Fm/FmController.h"
  #include "Gyro/GyroController.h"
  #include "Serial/SerialController.h"
  #include "Motor/MotorController.h"
  #include "Motor/Mode/MotorModeChannelMap.h"
  #include "Board/BoardSetup.h"

  class DroneController
  {
    private:
    FmController *MyFmController;
    GyroController *MyGyroController;
    SerialController *MySerialController;
    TaskController *MyTaskController;
    MotorController *MyMotorController;
    Button *MotorOnOffButton;

    public:
    DroneController(BoardSetup *boardSetup);
    void Setup();
    void Loop();
  };

#endif
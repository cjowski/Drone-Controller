#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

  #include "Fm/FmController.h"
  #include "Gyro/GyroController.h"
  #include "Serial/SerialController.h"
  #include "Motor/MotorController.h"
  #include "Motor/Mode/MotorModeChannelMap.h"

  class DroneController
  {
    private:
    FmController *MyFmController;
    GyroController *MyGyroController;
    SerialController *MySerialController;
    TaskController *MyTaskController;
    MotorController *MyMotorController;

    public:
    DroneController();
    void Loop();
  };

#endif
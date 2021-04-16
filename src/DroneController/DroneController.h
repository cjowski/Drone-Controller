#ifndef DRONE_CONTROLLER_H
#define DRONE_CONTROLLER_H

  #include "Fm/FmController.h"
  #include "Gyro/GyroController.h"
  #include "Serial/SerialController.h"
  #include "Motor/Motor.h"

  class DroneController
  {
    private:
    FmController *MyFmController;
    GyroController *MyGyroController;
    SerialController *MySerialController;
    TaskController *MyTaskController;
    Motor *MyMotor;

    public:
    DroneController();
    void Loop();
  };

#endif
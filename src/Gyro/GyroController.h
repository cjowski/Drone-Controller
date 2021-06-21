#ifndef GYRO_CONTROLLER_H
#define GYRO_CONTROLLER_H

  #include "Gyro.h"
  #include "GyroAngles.h"

  class GyroController
  {
    public:
    GyroController();
    SerialEncoderInput *GetSerialEncoderInput();
    void Loop();

    private:
    Gyro *MyGyro;
    GyroAngles *MyGyroAngles;
  };

#endif
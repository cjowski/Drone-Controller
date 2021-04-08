#ifndef GYRO_CONTROLLER_H
#define GYRO_CONTROLLER_H

  #include "Gyro.h"
  #include "GyroAngles.h"
  #include "GyroSerialValue.h"

  class GyroController
  {
    public:
    GyroController();
    GyroSerialValue *GetSerialValue();
    void Loop();

    private:
    Gyro *MyGyro;
    GyroAngles *MyGyroAngles;
  };

#endif
#ifndef GYRO_CONTROLLER_H
#define GYRO_CONTROLLER_H

  #include "Gyro/Gyro.h"
  #include "Gyro/GyroAngles.h"

  class GyroController
  {
    public:
    GyroController();
    std::list<String> GetPrintStrings();
    void Loop();

    private:
    Gyro *MyGyro;
    GyroAngles *MyGyroAngles;
  };

#endif
#ifndef GYRO_OUTPUT_H
#define GYRO_OUTPUT_H

  #include <stdint.h>

  struct GyroOutput
  {
    bool CalibrationDone;

    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;

    int16_t AccelerometerX;
    int16_t AccelerometerY;
    int16_t AccelerometerZ;
  };

#endif
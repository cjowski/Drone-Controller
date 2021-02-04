#ifndef GYRO_H
#define GYRO_H

  #include "Wire.h"
  #include "GyroOutput.h"

  class Gyro
  {
    private:
    const int MPU_ADDR = 0x68;
    const int PWR_MGMT_1_REGISTER = 0x6B;
    const int START_READ_REGISTER = 0x3B;
    const int REGISTERS_COUNT = 14;
    const int GYRO_REFRESH_RATE = 250;
    const float ANGLE_PER_SEC = 131;
    const int CALIBRATION_CHECKS = 2000;

    float UpdatePeriod;
    uint32_t PreviousReadTime;

    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;

    int16_t Temperature;

    int16_t AccelerometerX;
    int16_t AccelerometerY;
    int16_t AccelerometerZ;
    
    float OffsetGyroX;
    float OffsetGyroY;
    float OffsetGyroZ;

    bool CalibrationDone;
    int CalibrationChecksLeft;

    float AngleMultiplier;

    void ApplyGyroOffset();
    void Calibrate();
    void ReadValues();
    
    public:
    Gyro();

    void Setup();
    void ReadOrCalibrate();
    float GetAngleMultiplayer();
    float GetUpdatePeriod();
    GyroOutput GetOutput();
  };

#endif
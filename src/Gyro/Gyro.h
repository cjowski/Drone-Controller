#ifndef GYRO_H
#define GYRO_H

  #include "Wire.h"

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
    const float TO_RADIANS_MULTIPLIER = ((float)PI / (float)180);

    float _updatePeriod = 0;
    uint32_t _previousReadTime = 0;

    int16_t _gyro_X;
    int16_t _gyro_Y;
    int16_t _gyro_Z;

    int16_t _temperature;

    int16_t _accelerometer_X;
    int16_t _accelerometer_Y;
    int16_t _accelerometer_Z;
    
    float _offset_gyro_X;
    float _offset_gyro_Y;
    float _offset_gyro_Z;
    int _calibrationChecksLeft;

    float _gyroMultiplier;

    void ApplyGyroOffset();
    float GetConvertedAngle(int16_t input);
    float GetRadians(float degrees);
    String GetString(int16_t input);
    String GetString(float input);
    
    public:
    Gyro();

    float AnglePitch;
    float AngleRoll;
    float AngleYaw;
    bool CalibrationDone;

    void Setup();
    void ReadOrCalibrate();
    void Calibrate();
    void ReadValues();
    void UpdateAngles();
    String ToString();
  };

#endif
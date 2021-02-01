#include "Gyro.h"

using namespace std;

Gyro::Gyro()
{
  AnglePitch = 0;
  AngleRoll = 0;
  AngleYaw = 0;
  CalibrationDone = false;
  _offset_gyro_X = 0;
  _offset_gyro_Y = 0;
  _offset_gyro_Z = 0;
  _calibrationChecksLeft = CALIBRATION_CHECKS;
  _gyroMultiplier = (float)1 / ANGLE_PER_SEC / (float)GYRO_REFRESH_RATE;
  _updatePeriod = (float)1000000 / (float)GYRO_REFRESH_RATE;
}

void Gyro::Setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(PWR_MGMT_1_REGISTER); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void Gyro::ReadOrCalibrate()
{
  uint32_t currentTime = micros();
  if (currentTime - _previousReadTime > _updatePeriod)
  {
    ReadValues();
    if (CalibrationDone)
    {
      ApplyGyroOffset();
      UpdateAngles();
    }
    else
    {
      Calibrate();
    }
    _previousReadTime = currentTime;
  }
}

void Gyro::Calibrate()
{
  if (_calibrationChecksLeft == 0)
  {
    _offset_gyro_X /= CALIBRATION_CHECKS;
    _offset_gyro_Y /= CALIBRATION_CHECKS;
    _offset_gyro_Z /= CALIBRATION_CHECKS;
    CalibrationDone = true;
  }
  else
  {
    // Serial.print("A ");
    // Serial.print(_offset_gyro_X);
    // Serial.print(" ");
    // Serial.print(_gyro_X);
    _offset_gyro_X += _gyro_X;
    _offset_gyro_Y += _gyro_Y;
    _offset_gyro_Z += _gyro_Z;
    _calibrationChecksLeft--;
    // Serial.print(" ");
    // Serial.println(_offset_gyro_X);
    // Serial.println();
  }
}

void Gyro::ReadValues()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(START_READ_REGISTER); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, REGISTERS_COUNT, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  _accelerometer_X = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  _accelerometer_Y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  _accelerometer_Z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  _temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  _gyro_X = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  _gyro_Y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  _gyro_Z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
}

void Gyro::UpdateAngles()
{
  float currentAnglePitch = GetConvertedAngle(_gyro_X);
  float currentAngleRoll = GetConvertedAngle(_gyro_Y);
  float currentAngleYaw = GetConvertedAngle(_gyro_Z);

  AnglePitch += currentAnglePitch;
  AngleRoll += currentAngleRoll;
  AngleYaw += currentAngleYaw;

  float angleYawTransition = sin(GetRadians(currentAngleYaw));
  AnglePitch += AngleRoll * angleYawTransition;
  AngleRoll -= AnglePitch * angleYawTransition;
}

String Gyro::ToString()
{
  return
    // GetString(_accelerometer_X)
    // + "|" + GetString(_accelerometer_Y)
    // + "|" + GetString(_accelerometer_Z)
    // + "|" + GetString(_temperature)
    // + "|" + GetString(AngleRoll)
    // + "|" + GetString(AnglePitch)
    // + "|" + GetString(AngleYaw);

    GetString(AnglePitch);
}

void Gyro::ApplyGyroOffset()
{
  _gyro_X -= _offset_gyro_X;
  _gyro_Y -= _offset_gyro_Y;
  _gyro_Z -= _offset_gyro_Z;
}

float Gyro::GetConvertedAngle(int16_t input) {
  return (float)input * _gyroMultiplier;
}

float Gyro::GetRadians(float degrees) {
  return degrees * TO_RADIANS_MULTIPLIER;
}

char buffer1[7];
String Gyro::GetString(int16_t input) {
  sprintf(buffer1, "%6d", input);
  return buffer1;
}

char buffer2[10];
String Gyro::GetString(float input) {
  dtostrf(input, 4, 6, buffer2);
  return buffer2;
}
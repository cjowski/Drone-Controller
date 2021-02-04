#include "Gyro.h"

using namespace std;

Gyro::Gyro()
{
  OffsetGyroX = 0;
  OffsetGyroY = 0;
  OffsetGyroZ = 0;
  CalibrationDone = false;
  CalibrationChecksLeft = CALIBRATION_CHECKS;
  AngleMultiplier = (float)1 / ANGLE_PER_SEC / (float)GYRO_REFRESH_RATE;
  UpdatePeriod = (float)1000000 / (float)GYRO_REFRESH_RATE;
  PreviousReadTime = 0;
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
  if (currentTime - PreviousReadTime > UpdatePeriod)
  {
    ReadValues();
    if (CalibrationDone)
    {
      ApplyGyroOffset();
    }
    else
    {
      Calibrate();
    }
    PreviousReadTime = currentTime;
  }
}

void Gyro::Calibrate()
{
  if (CalibrationChecksLeft == 0)
  {
    OffsetGyroX /= CALIBRATION_CHECKS;
    OffsetGyroY /= CALIBRATION_CHECKS;
    OffsetGyroZ /= CALIBRATION_CHECKS;
    CalibrationDone = true;
  }
  else
  {
    OffsetGyroX += GyroX;
    OffsetGyroY += GyroY;
    OffsetGyroZ += GyroZ;
    CalibrationChecksLeft--;
  }
}

void Gyro::ReadValues()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(START_READ_REGISTER); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, REGISTERS_COUNT, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  AccelerometerX = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  AccelerometerY = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  AccelerometerZ = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  Temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  GyroX = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  GyroY = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  GyroZ = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
}

void Gyro::ApplyGyroOffset()
{
  GyroX -= OffsetGyroX;
  GyroY -= OffsetGyroY;
  GyroZ -= OffsetGyroZ;
}

float Gyro::GetAngleMultiplayer()
{
  return AngleMultiplier;
}

float Gyro::GetUpdatePeriod()
{
  return UpdatePeriod;
}

GyroOutput Gyro::GetOutput()
{
  GyroOutput output;
  output.CalibrationDone = CalibrationDone;

  output.GyroX = GyroX;
  output.GyroY = GyroY;
  output.GyroZ = GyroZ;

  output.AccelerometerX = AccelerometerX;
  output.AccelerometerY = AccelerometerY;
  output.AccelerometerZ = AccelerometerZ;

  return output;
}
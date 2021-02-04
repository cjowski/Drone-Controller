#include "GyroAngles.h"

GyroAngles::GyroAngles(float angleMultiplier, float updatePeriod)
{
  Pitch = 0;
  Roll = 0;
  Yaw = 0;
  AngleMultiplier = angleMultiplier;
  UpdatePeriod = updatePeriod;
  PreviousReadTime = 0;
}

void GyroAngles::TryUpdateAngles(GyroOutput gyroOutput)
{
  uint32_t currentTime = micros();
  if (gyroOutput.CalibrationDone && currentTime - PreviousReadTime > UpdatePeriod)
  {
    PreviousReadTime = currentTime;

    float currentAnglePitch = GetConvertedAngle(gyroOutput.GyroX);
    float currentAngleRoll = GetConvertedAngle(gyroOutput.GyroY);
    float currentAngleYaw = GetConvertedAngle(gyroOutput.GyroZ);

    Pitch += currentAnglePitch;
    Roll += currentAngleRoll;
    Yaw += currentAngleYaw;

    float angleYawTransition = sin(GetRadians(currentAngleYaw));
    Pitch += Roll * angleYawTransition;
    Roll -= Pitch * angleYawTransition;
  }
}

float GyroAngles::GetConvertedAngle(int16_t input) {
  return (float)input * AngleMultiplier;
}

float GyroAngles::GetRadians(float degrees) {
  return degrees * TO_RADIANS_MULTIPLIER;
}

String GyroAngles::ToString()
{
  return
    // GetString(_accelerometer_X)
    // + "|" + GetString(_accelerometer_Y)
    // + "|" + GetString(_accelerometer_Z)
    // + "|" + GetString(_temperature)
    // + "|" + GetString(AngleRoll)
    // + "|" + GetString(AnglePitch)
    // + "|" + GetString(AngleYaw);

    String(Pitch, 4);
}
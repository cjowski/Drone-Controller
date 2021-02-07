#include "GyroAngles.h"

GyroAngles::GyroAngles(float angleMultiplier, float updatePeriod)
{
  Pitch = 0;
  Roll = 0;
  Yaw = 0;
  AngleMultiplier = angleMultiplier;
  CalibrationDone = false;
  UpdatePeriod = updatePeriod;
  PreviousReadTime = 0;
}

void GyroAngles::TryUpdateAngles(GyroOutput gyroOutput)
{
  uint32_t currentTime = micros();
  if (gyroOutput.CalibrationDone && currentTime - PreviousReadTime > UpdatePeriod)
  {
    CalibrationDone = true;
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

std::list<String> GyroAngles::ToStringList()
{
  std::list<String> outputList;

  outputList.push_back(
    String(millis())
  );

  outputList.push_back(
    String(CalibrationDone)
  );

  outputList.push_back(
    String(Pitch, 4)
  );

  outputList.push_back(
    String(Roll, 4)
  );

  outputList.push_back(
    String(Yaw, 4)
  );

  return outputList;
}
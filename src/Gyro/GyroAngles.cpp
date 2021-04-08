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
  SetGyroAngles = false;
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

    float totalAccelerometerVector = sqrt(
      (gyroOutput.AccelerometerX * gyroOutput.AccelerometerX)
      + (gyroOutput.AccelerometerY * gyroOutput.AccelerometerY)
      + (gyroOutput.AccelerometerZ * gyroOutput.AccelerometerZ)
    );

    float pitchAcceleration = asin(gyroOutput.AccelerometerY / totalAccelerometerVector) * ((float)1 / TO_RADIANS_MULTIPLIER);
    float rollAcceleration = asin(gyroOutput.AccelerometerX / totalAccelerometerVector) * ((float)-1 / TO_RADIANS_MULTIPLIER);

    if (SetGyroAngles)
    {
      Pitch = Pitch * 0.9996 + pitchAcceleration * 0.0004;
      Roll = Roll * 0.9996 + rollAcceleration * 0.0004;
    }
    else
    {
      Pitch = pitchAcceleration;
      Roll = rollAcceleration;
      SetGyroAngles = true;
    }
  }
}

float GyroAngles::GetConvertedAngle(int16_t input) {
  return (float)input * AngleMultiplier;
}

float GyroAngles::GetRadians(float degrees) {
  return degrees * TO_RADIANS_MULTIPLIER;
}

GyroSerialValue* GyroAngles::GetSerialValue()
{
  return new GyroSerialValue(
    (long)millis(),
    CalibrationDone,
    Pitch,
    Roll,
    Yaw
  );
}
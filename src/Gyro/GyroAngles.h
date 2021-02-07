#ifndef GYRO_ANGLES_H
#define GYRO_ANGLES_H

  #include <math.h>
  #include <WString.h>
  #include <list>
  #include <wiring_time.h>
  #include <wiring_constants.h>
  #include "GyroOutput.h"

  class GyroAngles
  {
    private:
    const float TO_RADIANS_MULTIPLIER = ((float)PI / (float)180);
    
    float Pitch;
    float Roll;
    float Yaw;
    float AngleMultiplier;

    bool CalibrationDone;

    float UpdatePeriod;
    uint32_t PreviousReadTime;

    public:
    GyroAngles(float updatePeriod, float angleMultiplier);
    void TryUpdateAngles(GyroOutput gyroOutput);
    float GetConvertedAngle(int16_t input);
    float GetRadians(float degrees);
    std::list<String> ToStringList();
  };

#endif
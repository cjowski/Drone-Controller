#include "GyroSerialValue.h"

GyroSerialValue::GyroSerialValue(
  long time,
  bool calibrationDone,
  float pitch,
  float roll,
  float yaw
)
{
  Time = time;
  CalibrationDone = calibrationDone;
  Pitch = pitch;
  Roll = roll;
  Yaw = yaw;
}

std::list<String> GyroSerialValue::GetPrintStrings()
{
  std::list<String> printStrings;
  printStrings.push_back(String(Time));
  printStrings.push_back(String(CalibrationDone));
  printStrings.push_back(String(Pitch, 4));
  printStrings.push_back(String(Roll, 4));
  printStrings.push_back(String(Yaw, 4));
  return printStrings; 
}
#include "MotorsSerialValue.h"

MotorsSerialValue::MotorsSerialValue(
  long time,
  int motorSpeed1,
  int motorSpeed2,
  int motorSpeed3,
  int motorSpeed4
)
{
  Time = time;
  MotorSpeed[0] = motorSpeed1;
  MotorSpeed[1] = motorSpeed2;
  MotorSpeed[2] = motorSpeed3;
  MotorSpeed[3] = motorSpeed4;
}

std::list<String> MotorsSerialValue::GetPrintStrings()
{
  std::list<String> printStrings;
  printStrings.push_back(String(Time));
  for (int i = 0; i < MOTORS_COUNT; i++)
  {
    printStrings.push_back(String(MotorSpeed[i]));
  }
  return printStrings; 
}
#include "GyroController.h"

GyroController::GyroController()
{
  MyGyro = new Gyro();
  MyGyroAngles = new GyroAngles(
    MyGyro->GetAngleMultiplayer(),
    MyGyro->GetUpdatePeriod()
  );
  MyGyro->Setup();
}

std::list<String> GyroController::GetPrintStrings()
{
  return MyGyroAngles->ToStringList();
}

void GyroController::Loop()
{
  MyGyro->ReadOrCalibrate();
  MyGyroAngles->TryUpdateAngles(
    MyGyro->GetOutput()
  );
}
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

GyroSerialValue* GyroController::GetSerialValue()
{
  return MyGyroAngles->GetSerialValue();
}

void GyroController::Loop()
{
  MyGyro->ReadOrCalibrate();
  MyGyroAngles->TryUpdateAngles(
    MyGyro->GetOutput()
  );
}
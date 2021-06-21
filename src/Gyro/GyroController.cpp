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

SerialEncoderInput* GyroController::GetSerialEncoderInput()
{
  return MyGyroAngles->GetSerialEncoderInput();
}

void GyroController::Loop()
{
  MyGyro->ReadOrCalibrate();
  MyGyroAngles->TryUpdateAngles(
    MyGyro->GetOutput()
  );
}
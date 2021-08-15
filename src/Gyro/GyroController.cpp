#include "GyroController.h"

GyroController::GyroController()
{
  MyGyro = new Gyro();
  MyGyroAngles = new GyroAngles(
    MyGyro->GetAngleMultiplayer(),
    MyGyro->GetUpdatePeriod()
  );
}

SerialEncoderInput* GyroController::GetSerialEncoderInput()
{
  return MyGyroAngles->GetSerialEncoderInput();
}

void GyroController::Setup()
{
  MyGyro->Setup();
}

void GyroController::Loop()
{
  MyGyro->ReadOrCalibrate();
  MyGyroAngles->TryUpdateAngles(
    MyGyro->GetOutput()
  );
}
#include "DroneController.h"

DroneController::DroneController() { }

void DroneController::Setup()
{
  SetupTimers();
  SetupFmChannelsContainer();
  SetupGyro();
  SetupSerials();
  SetupSerialPrinters(&Serial);
}

void DroneController::SetupSerials()
{
  Serial.begin(SERIAL_BAUD_RATE); 
  HardwareSerial Serial1(SERIAL1_RX_PIN, SERIAL1_TX_PIN);
  Serial1.begin(SERIAL_BAUD_RATE);
}

void DroneController::SetupTimers()
{
  MyTimerController = new Timer2(&HardwareTimer2);
  MyTimerController->Setup();
  MyTimerController->SetupChannel(1);
  MyTimerController->SetupChannel(2);
  MyTimerController->SetupChannel(3);
  MyTimerController->SetupChannel(4);
  MyTimerController->Resume();
}

void DroneController::SetupFmChannelsContainer()
{
  FmChannel *channels = new FmChannel[CHANNELS_COUNT];

  for (int i = 0; i < CHANNELS_COUNT; i++) {
    channels[i].AttachUpdateValueCallback(
      [&, i, channels] () {
        channels[i].TrySetNewValue(
          MyTimerController->GetChannelValue(i + 1)
        );
      }
    );
  }

  MyFmChannelsContainer = new FmChannelsContainer(channels, CHANNELS_COUNT);
}

void DroneController::SetupGyro()
{
  MyGyro = new Gyro();
  MyGyroAngles = new GyroAngles(
    MyGyro->GetAngleMultiplayer(),
    MyGyro->GetUpdatePeriod()
  );
  MyGyro->Setup();
}

void DroneController::SetupSerialPrinters(HardwareSerial *printerSerial)
{
  SerialPrinterFm = new SerialPrinter(
    printerSerial,
    [&] ()->String {
      return MyFmChannelsContainer->ToSerialString();
    },
    500
  );

  SerialPrinterGyro = new SerialPrinter(
    printerSerial,
    [&] ()->String {
      return MyGyroAngles->ToSerialString();
    },
    1000
  );
}

void DroneController::Loop()
{
  UpdateFmChannelsState();
  UpdateGyroState();
}

void DroneController::UpdateFmChannelsState()
{
  MyFmChannelsContainer->UpdateChannelsValues();
}

void DroneController::UpdateGyroState()
{
  MyGyro->ReadOrCalibrate();
  MyGyroAngles->TryUpdateAngles(
    MyGyro->GetOutput()
  );
}

void DroneController::SerialPrint()
{
  SerialPrinterFm->SerialPrintln();
  SerialPrinterGyro->SerialPrintln();
}
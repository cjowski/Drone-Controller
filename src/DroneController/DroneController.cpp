#include "DroneController.h"

DroneController::DroneController() { }

void DroneController::Setup()
{
  SetupTimers();
  SetupFmChannelsContainer();
  SetupGyro();
  SetupSerials();
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

void DroneController::SetupSerials()
{
  PrinterSerial = new HardwareSerial(SERIAL1_RX_PIN, SERIAL1_TX_PIN);
  PrinterSerial->begin(SERIAL_BAUD_RATE);
  SetupSerialPrinters();
}

void DroneController::SetupSerialPrinters()
{
  SerialPrinterFm = new SerialPrinter(
    PrinterSerial,
    [&] ()->std::list<String> {
      return MyFmChannelsContainer->ToStringList();
    },
    'F',
    50
  );

  SerialPrinterGyro = new SerialPrinter(
    PrinterSerial,
    [&] ()->std::list<String> {
      return MyGyroAngles->ToStringList();
    },
    'G',
    120
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
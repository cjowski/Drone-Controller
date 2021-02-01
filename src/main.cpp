#include <Arduino.h>
#include "Fm\TimerController\Timer2.h"
#include "Fm\FmChannels\FmChannelsContainer.h"
#include "Gyro/Gyro.h"

#define SERIAL1_TX_PIN PA9
#define SERIAL1_RX_PIN PA10
#define SERIAL_BAUD_RATE 9600

#define CHANNELS_COUNT 4

uint32_t previousPrintTime = 0; 
HardwareTimer hTimer2 = HardwareTimer(TIM2);
TimerController *timer2 = new Timer2(&hTimer2);

HardwareSerial Serial1(SERIAL1_RX_PIN, SERIAL1_TX_PIN);

FmChannelsContainer *fmChannelsContainer;

Gyro *gyro;

void SetupSerials()
{
  Serial.begin(SERIAL_BAUD_RATE); 
  Serial1.begin(SERIAL_BAUD_RATE);
}

void SetupTimers()
{
  timer2->Setup();
  timer2->SetupChannel(1);
  timer2->SetupChannel(2);
  timer2->SetupChannel(3);
  timer2->SetupChannel(4);
  timer2->Resume();
}

void SetupFmChannelsContainer()
{
  FmChannel *channels = new FmChannel[CHANNELS_COUNT];

  for (int i = 0; i < CHANNELS_COUNT; i++) {
    channels[i].AttachUpdateValueCallback(
      [i, channels] () {
        channels[i].TrySetNewValue(
          timer2->GetChannelValue(i + 1)
        );
      }
    );
  }

  fmChannelsContainer = new FmChannelsContainer(channels, CHANNELS_COUNT);
}

void SetupGyro()
{
  gyro = new Gyro();
  gyro->Setup();
}

void setup() {
  SetupSerials();
  SetupTimers();
  SetupFmChannelsContainer();
  SetupGyro();
  delay(250);
}

void loop() {
  fmChannelsContainer->UpdateChannelsValues();
  gyro->ReadOrCalibrate();

  if (millis() - previousPrintTime > 500) {

    Serial.println(gyro->ToString());
    // Serial1.print(
    //   fmChannelsContainer->ToSerialString()
    // );
    // Serial.println(
    //   fmChannelsContainer->ToSerialString()
    // );

    previousPrintTime = millis();
  }
}
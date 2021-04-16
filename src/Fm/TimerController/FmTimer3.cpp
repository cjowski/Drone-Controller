#include "FmTimer3.h"

FmTimer3::FmTimer3(HardwareTimer *timer)
{
  Timer = timer;
  Channels = new FmTimerChannel[4];
  Channels[0] = FmTimerChannel(1, timer);
  Channels[1] = FmTimerChannel(2, timer);
  Channels[2] = FmTimerChannel(3, timer);
  Channels[3] = FmTimerChannel(4, timer);
}

void FmTimer3::Setup()
{
  TIM3->CR1 = TIM_CR1_CEN;
  TIM3->CR2 = 0;
  TIM3->SMCR = 0;
  TIM3->DIER = TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE;
  TIM3->EGR = 0;
  TIM3->CCMR1 = TIM_CCMR1_CC1S_1;
  TIM3->CCMR2 = 0;
  TIM3->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  TIM3->PSC = 71;
  TIM3->ARR = 0xFFFF;
  TIM3->DCR = 0;
}

void FmTimer3::SetupChannel(int channelNo)
{
  switch(channelNo)
  {
    case 1:
      Channels[0].Setup(
        CH1_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM3->CCR1,
        &TIM3->CCER,
        TIM_CCER_CC1P
      );
      break;
    case 2:
      Channels[1].Setup(
        CH2_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM3->CCR2,
        &TIM3->CCER,
        TIM_CCER_CC2P
      );
      break;
    case 3:
      Channels[2].Setup(
        CH3_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM3->CCR3,
        &TIM3->CCER,
        TIM_CCER_CC3P
      );
      break;
    case 4:
      Channels[3].Setup(
        CH4_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM3->CCR4,
        &TIM3->CCER,
        TIM_CCER_CC4P
      );
  };
}
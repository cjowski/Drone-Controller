#include "Timer2.h"

Timer2::Timer2(HardwareTimer *timer)
{
  Timer = timer;
  Channels = new TimerChannel[4];
  Channels[0] = TimerChannel(1, timer);
  Channels[1] = TimerChannel(2, timer);
  Channels[2] = TimerChannel(3, timer);
  Channels[3] = TimerChannel(4, timer);
}

void Timer2::Setup()
{
  TIM2->CR1 = TIM_CR1_CEN;
  TIM2->CR2 = 0;
  TIM2->SMCR = 0;
  TIM2->DIER = TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE;
  TIM2->EGR = 0;
  TIM2->CCMR1 = TIM_CCMR1_CC1S_1;
  TIM2->CCMR2 = 0;
  TIM2->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  TIM2->PSC = 71;
  TIM2->ARR = 0xFFFF;
  TIM2->DCR = 0;
}

void Timer2::SetupChannel(int channelNo)
{
  switch(channelNo)
  {
    case 1:
      Channels[0].Setup(
        CH1_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM2->CCR1,
        &TIM2->CCER,
        TIM_CCER_CC1P
      );
      break;
    case 2:
      Channels[1].Setup(
        CH2_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM2->CCR2,
        &TIM2->CCER,
        TIM_CCER_CC2P
      );
      break;
    case 3:
      Channels[2].Setup(
        CH3_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM2->CCR3,
        &TIM2->CCER,
        TIM_CCER_CC3P
      );
      break;
    case 4:
      Channels[3].Setup(
        CH4_PIN,
        TIMER_INPUT_CAPTURE_RISING,
        &TIM2->CCR4,
        &TIM2->CCER,
        TIM_CCER_CC4P
      );
  };
}
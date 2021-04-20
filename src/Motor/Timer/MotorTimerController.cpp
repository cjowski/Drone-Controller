#include "MotorTimerController.h"

void MotorTimerController::Setup()
{
  TIMER_BASE()->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
  TIMER_BASE()->CR2 = 0;
  TIMER_BASE()->SMCR = 0;
  TIMER_BASE()->DIER = 0;
  TIMER_BASE()->EGR = 0;
  TIMER_BASE()->CCMR1 = (0b110 << 4) | TIM_CCMR1_OC1PE |(0b110 << 12) | TIM_CCMR1_OC2PE;
  TIMER_BASE()->CCMR2 = (0b110 << 4) | TIM_CCMR2_OC3PE |(0b110 << 12) | TIM_CCMR2_OC4PE;
  TIMER_BASE()->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  TIMER_BASE()->PSC = 71;
  TIMER_BASE()->ARR = 5000;
  TIMER_BASE()->DCR = 0;
}

void MotorTimerController::SetupChannel(int channelNo)
{
  if (channelNo > MAX_CHANNELS_COUNT || channelNo > CHANNELS_COUNT())
  {
    return;
  }

  pinMode(CHANNEL_PINS()[channelNo - 1], OUTPUT);
  Timer->setMode(
    channelNo,
    TIMER_OUTPUT_COMPARE_PWM1,
    CHANNEL_PINS()[channelNo - 1]
  );
  SetChannelValue(channelNo, MotorTimerController::MIN_PWM_VALUE);
}

void MotorTimerController::Resume()
{
  Timer->resume();
}

void MotorTimerController::Refresh()
{
  Timer->refresh();
}

void MotorTimerController::SetChannelValue(
  int channelNo,
  uint32_t value
)
{
  switch (channelNo)
  {
    case 1:
      TIMER_BASE()->CCR1 = value;
      break;
    case 2:
      TIMER_BASE()->CCR2 = value;
      break;
    case 3:
      TIMER_BASE()->CCR3 = value;
      break;
    case 4:
      TIMER_BASE()->CCR4 = value;
      break;
    default:
      return;
  }
}
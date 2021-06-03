#include "MotorTimerController.h"

MotorTimerController::MotorTimerController(const BoardTimer *motorBoardTimer)
{
  MotorBoardTimer = motorBoardTimer;
  Timer = new HardwareTimer(motorBoardTimer->TIMER_BASE());
}

void MotorTimerController::Setup()
{
  MotorBoardTimer->TIMER_BASE()->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
  MotorBoardTimer->TIMER_BASE()->CR2 = 0;
  MotorBoardTimer->TIMER_BASE()->SMCR = 0;
  MotorBoardTimer->TIMER_BASE()->DIER = 0;
  MotorBoardTimer->TIMER_BASE()->EGR = 0;
  MotorBoardTimer->TIMER_BASE()->CCMR1 = (0b110 << 4) | TIM_CCMR1_OC1PE |(0b110 << 12) | TIM_CCMR1_OC2PE;
  MotorBoardTimer->TIMER_BASE()->CCMR2 = (0b110 << 4) | TIM_CCMR2_OC3PE |(0b110 << 12) | TIM_CCMR2_OC4PE;
  MotorBoardTimer->TIMER_BASE()->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  MotorBoardTimer->TIMER_BASE()->PSC = 71;
  MotorBoardTimer->TIMER_BASE()->ARR = 5000;
  MotorBoardTimer->TIMER_BASE()->DCR = 0;
}

void MotorTimerController::SetupChannel(int channelNo)
{
  if (channelNo > MAX_CHANNELS_COUNT || channelNo > MotorBoardTimer->CHANNELS_COUNT())
  {
    return;
  }

  pinMode(MotorBoardTimer->CHANNEL_PINS()[channelNo - 1], OUTPUT);
  Timer->setMode(
    channelNo,
    TIMER_OUTPUT_COMPARE_PWM1,
    MotorBoardTimer->CHANNEL_PINS()[channelNo - 1]
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
      MotorBoardTimer->TIMER_BASE()->CCR1 = value;
      break;
    case 2:
      MotorBoardTimer->TIMER_BASE()->CCR2 = value;
      break;
    case 3:
      MotorBoardTimer->TIMER_BASE()->CCR3 = value;
      break;
    case 4:
      MotorBoardTimer->TIMER_BASE()->CCR4 = value;
      break;
    default:
      return;
  }
}
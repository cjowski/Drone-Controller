#include "FmTimerController.h"

void FmTimerController::Setup()
{
  TIMER_BASE()->CR1 = TIM_CR1_CEN;
  TIMER_BASE()->CR2 = 0;
  TIMER_BASE()->SMCR = 0;
  TIMER_BASE()->DIER = TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE;
  TIMER_BASE()->EGR = 0;
  TIMER_BASE()->CCMR1 = TIM_CCMR1_CC1S_1;
  TIMER_BASE()->CCMR2 = 0;
  TIMER_BASE()->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  TIMER_BASE()->PSC = 71;
  TIMER_BASE()->ARR = 0xFFFF;
  TIMER_BASE()->DCR = 0;
}

void FmTimerController::SetupChannel(int channelNo)
{
  if (channelNo > MAX_CHANNELS_COUNT || channelNo > CHANNELS_COUNT())
  {
    return;
  }

  volatile uint32_t *captureCompareRegister;
  unsigned long captureCompareOutPolarity;
  switch (channelNo)
  {
    case 1:
      captureCompareRegister = &TIMER_BASE()->CCR1;
      captureCompareOutPolarity = TIM_CCER_CC1P;
      break;
    case 2:
      captureCompareRegister = &TIMER_BASE()->CCR2;
      captureCompareOutPolarity = TIM_CCER_CC2P;
      break;
    case 3:
      captureCompareRegister = &TIMER_BASE()->CCR3;
      captureCompareOutPolarity = TIM_CCER_CC3P;
      break;
    case 4:
      captureCompareRegister = &TIMER_BASE()->CCR4;
      captureCompareOutPolarity = TIM_CCER_CC4P;
      break;
    default:
      return;
  }

  FmTimerChannel *fmTimerChannel = new FmTimerChannel(
    channelNo,
    CHANNEL_PINS()[channelNo - 1],
    Timer
  );

  fmTimerChannel->Setup(
    captureCompareRegister,
    &TIMER_BASE()->CCER,
    captureCompareOutPolarity
  );
  
  Channels.push_back(fmTimerChannel);
}

void FmTimerController::Resume()
{
  Timer->resume();
}

void FmTimerController::Refresh()
{
  Timer->refresh();
}

int32_t FmTimerController::GetChannelValue(int channelNo)
{
  for (auto it = Channels.begin(); it != Channels.end(); it++)
  {
    if ((*it)->GetChannelNo() == channelNo)
    {
      return (*it)->GetOutputValue();
    }
  }
  return -1;
}
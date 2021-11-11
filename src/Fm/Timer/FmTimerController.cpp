#include "FmTimerController.h"

FmTimerController::FmTimerController(
  const BoardTimerSetup *fmBoardTimerSetup
)
{
  FmBoardTimerSetup = fmBoardTimerSetup;
}

void FmTimerController::Setup()
{
  std::map<int, HardwareTimer*> initializedTimers;
  for (int i = 0; i < FmBoardTimerSetup->GetChannelsCount(); i++)
  {
    if (i >= MAX_CHANNELS_COUNT || i >= FmBoardTimerSetup->GetChannelsCount())
    {
      return;
    }

    auto channelSetup = FmBoardTimerSetup->GetChannelSetup(i);
    auto timerNo = channelSetup->GetTimerNo();

    if (initializedTimers.find(timerNo) == initializedTimers.end())
    {
      initializedTimers[timerNo] = new HardwareTimer(channelSetup->GetTimerBase());
      SetupTimer(channelSetup->GetTimerBase());
    }

    auto timer = initializedTimers.find(timerNo)->second;
    SetupChannel(channelSetup, timer);
  }
}

void FmTimerController::SetupTimer(TIM_TypeDef* timerBase)
{
  timerBase->CR1 = TIM_CR1_CEN;
  timerBase->CR2 = 0;
  timerBase->SMCR = 0;
  timerBase->DIER = TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE;
  timerBase->EGR = 0;
  timerBase->CCMR1 = TIM_CCMR1_CC1S_1;
  timerBase->CCMR2 = 0;
  timerBase->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  timerBase->PSC = 71;
  timerBase->ARR = 0xFFFF;
  timerBase->DCR = 0;
}

void FmTimerController::SetupChannel(
  BoardTimerChannelSetup *channelSetup,
  HardwareTimer *timer
)
{
  FmTimerChannel *fmTimerChannel = new FmTimerChannel(
    channelSetup->GetChannelNo(),
    channelSetup->GetTimerNo(),
    channelSetup->GetPin(),
    timer
  );
  Channels.push_back(fmTimerChannel);
  fmTimerChannel->Setup(channelSetup);
}

void FmTimerController::Resume()
{
  auto timers = GetTimers();
  for (auto it = timers.begin(); it != timers.end(); it++)
  {
    (*it)->resume();
  }
}

void FmTimerController::Refresh()
{
  auto timers = GetTimers();
  for (auto it = timers.begin(); it != timers.end(); it++)
  {
    (*it)->refresh();
  }
}

int32_t FmTimerController::GetChannelValue(int channelIndex)
{
  auto it = Channels.begin();
  std::advance(it, channelIndex);
  return (*it)->GetOutputValue();
}

std::list<HardwareTimer*> FmTimerController::GetTimers()
{
  std::list<HardwareTimer*> timers;
  std::set<int> addedTimerNumbers;

  for (auto it = Channels.begin(); it != Channels.end(); it++)
  {
    if (addedTimerNumbers.find((*it)->GetTimerNo()) == addedTimerNumbers.end()){
      addedTimerNumbers.insert((*it)->GetTimerNo());
      timers.push_back((*it)->GetTimer());
    }
  }

  return timers;
}
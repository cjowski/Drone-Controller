#include "MotorTimerController.h"

MotorTimerController::MotorTimerController(
  const BoardTimerSetup *motorBoardTimerSetup
)
{
  MotorBoardTimerSetup = motorBoardTimerSetup;
}

void MotorTimerController::Setup()
{
  std::map<int, HardwareTimer*> initializedTimers;
  for (int i = 0; i < MotorBoardTimerSetup->GetChannelsCount(); i++)
  {
    if (i >= MAX_CHANNELS_COUNT || i >= MotorBoardTimerSetup->GetChannelsCount())
    {
      return;
    }

    auto channelSetup = MotorBoardTimerSetup->GetChannelSetup(i);
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

void MotorTimerController::SetupTimer(TIM_TypeDef* timerBase)
{
  timerBase->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
  timerBase->CR2 = 0;
  timerBase->SMCR = 0;
  timerBase->DIER = 0;
  timerBase->EGR = 0;
  timerBase->CCMR1 = (0b110 << 4) | TIM_CCMR1_OC1PE |(0b110 << 12) | TIM_CCMR1_OC2PE;
  timerBase->CCMR2 = (0b110 << 4) | TIM_CCMR2_OC3PE |(0b110 << 12) | TIM_CCMR2_OC4PE;
  timerBase->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  timerBase->PSC = 71;
  timerBase->ARR = 5000;
  timerBase->DCR = 0;
}

void MotorTimerController::SetupChannel(
  BoardTimerChannelSetup *channelSetup,
  HardwareTimer *timer
)
{
  pinMode(channelSetup->GetPin(), OUTPUT);
  timer->setMode(
    channelSetup->GetChannelNo(),
    TIMER_OUTPUT_COMPARE_PWM1,
    channelSetup->GetPin()
  );
  auto motorTimerChannel = new MotorTimerChannel(
    channelSetup->GetChannelNo(),
    channelSetup->GetTimerNo(),
    timer,
    channelSetup->GetTimerBase()
  );
  motorTimerChannel->SetValue(MotorTimerController::MIN_PWM_VALUE);
  Channels.push_back(motorTimerChannel);
}

void MotorTimerController::Resume()
{
  auto timers = GetTimers();
  for (auto it = timers.begin(); it != timers.end(); it++)
  {
    (*it)->resume();
  }
}

void MotorTimerController::Refresh()
{
  auto timers = GetTimers();
  for (auto it = timers.begin(); it != timers.end(); it++)
  {
    (*it)->refresh();
  }
}

void MotorTimerController::SetChannelValue(int channelNo, uint32_t value)
{
  if (channelNo > MAX_CHANNELS_COUNT)
  {
    return;
  }

  auto channel = GetChannel(channelNo);
  channel->SetValue(value);
}

MotorTimerChannel *MotorTimerController::GetChannel(int channelNo)
{
  auto it = Channels.begin();
  std::advance(it, channelNo - 1);
  return *it;
}

std::list<HardwareTimer*> MotorTimerController::GetTimers()
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


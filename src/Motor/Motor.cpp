#include "Motor.h"

Motor::Motor(
  int minChannelValue,
  int maxChannelValue,
  std::function<bool(void)> isFmSignalActive,
  std::function<int(void)> getFmChannelValue
)
{
  MinChannelValue = minChannelValue;
  MaxChannelValue = maxChannelValue;
  IsFmSignalActive = isFmSignalActive;
  GetFmChannelValue = getFmChannelValue;
  SetupTimer();
}

void Motor::SetupTimer()
{
  // TIMER_BASE()->CR1 = TIM_CR1_CEN;
  // TIMER_BASE()->CR2 = 0;
  // TIMER_BASE()->SMCR = 0;
  // TIMER_BASE()->DIER = TIM_DIER_CC1IE | TIM_DIER_CC2IE | TIM_DIER_CC3IE | TIM_DIER_CC4IE;
  // TIMER_BASE()->EGR = 0;
  // TIMER_BASE()->CCMR1 = TIM_CCMR1_CC1S_1;
  // TIMER_BASE()->CCMR2 = 0;
  // TIMER_BASE()->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  // TIMER_BASE()->PSC = 71;
  // TIMER_BASE()->ARR = 0xFFFF;
  // TIMER_BASE()->DCR = 0;

  TIM3->CR1 = TIM_CR1_CEN | TIM_CR1_ARPE;
  TIM3->CR2 = 0;
  TIM3->SMCR = 0;
  TIM3->DIER = 0;
  TIM3->EGR = 0;
  TIM3->CCMR1 = (0b110 << 4) | TIM_CCMR1_OC1PE |(0b110 << 12) | TIM_CCMR1_OC2PE;
  TIM3->CCMR2 = (0b110 << 4) | TIM_CCMR2_OC3PE |(0b110 << 12) | TIM_CCMR2_OC4PE;
  TIM3->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
  TIM3->PSC = 71;
  TIM3->ARR = 5000;
  TIM3->DCR = 0;

  TIM3->CCR1 = 1000;
  // TIM3->CCR2 = 1000;
  // TIM3->CCR3 = 1000;
  // TIM3->CCR4 = 1000;

  pinMode(PWM_PIN, OUTPUT);

  MotorTimer.setMode(
    1,
    TIMER_OUTPUT_COMPARE_PWM1,
    PWM_PIN
  );
  // MotorTimer.setOverflow(
  //   24000,
  //   HERTZ_FORMAT
  // );
}

int Motor::GetSpeed()
{
  if (!IsFmSignalActive())
  {
    return PreviousSpeed;
  }

  int mappedValue = MapFmChannelValueToSpeed(
    GetFmChannelValue()
  );

  if (mappedValue < MIN_SPEED)
  {
    return MIN_SPEED;
  }

  if (mappedValue > MAX_SPEED)
  {
    return MAX_SPEED;
  }

  return mappedValue;
}

int Motor::MapFmChannelValueToSpeed(int fmChannelValue)
{
  if (fmChannelValue < MinChannelValue)
  {
    return MIN_SPEED;
  }

  if (fmChannelValue > MaxChannelValue)
  {
    return MAX_SPEED;
  }

  return (fmChannelValue - MinChannelValue)
    * (MAX_MAP_VALUE - MIN_MAP_VALUE)
    / (MaxChannelValue - MinChannelValue)
    + MIN_MAP_VALUE;
}

void Motor::Loop()
{
  int currentSpeed = GetSpeed();
  // TIM3->CNT = 5000;
  TIM3->CCR1 = currentSpeed;
  // TIM3->CCR2 = currentSpeed;
  // TIM3->CCR3 = currentSpeed;
  // TIM3->CCR4 = currentSpeed;
  // 
  PreviousSpeed = currentSpeed;

  long currentTime = millis();
  if (currentTime - PreviousPrintTime > 500)
  {
    Serial.println(currentSpeed);
    PreviousPrintTime = currentTime;
  }

  MotorTimer.resume();
}
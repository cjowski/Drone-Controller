#include "FmChannel.h"

FmChannel::FmChannel()
{
  Value = -1;
}

void FmChannel::AttachUpdateValueCallback(std::function<void(void)> callback)
{
  UpdateValueCallback = callback;
}

int32_t FmChannel::GetValue()
{
  return Value;
}

void FmChannel::AddToPreviousValues(int32_t value)
{
  if (PreviousValues.size() == (unsigned int)MAX_PREVIOUS_VALUES_LENGTH)
  {
    PreviousValues.pop_front();
  }
  PreviousValues.push_back(value);
}

bool FmChannel::CanUpdateValue()
{
  return millis() > stopUpdateUntilTime;
}

bool FmChannel::MinMaxValid(int32_t newValue)
{
  return newValue > MIN_VALUE && newValue < MAX_VALUE;
}

bool FmChannel::ComparedToPreviousValuesValid(int32_t newValue)
{
  int wrongValuesCount = 0;
  std::list<int32_t>::iterator it;
  for (it = PreviousValues.begin(); it != PreviousValues.end(); it++)
  {
    if (abs(newValue - (*it)) > ALLOWED_VALUE_DIFFERENCE)
    {
      wrongValuesCount++;
    }
  }

  return wrongValuesCount <= MAX_ALLOWED_WRONG_VALUES;
}

bool FmChannel::PositiveSignalValid(int32_t newValue)
{
  return abs(newValue - PreviousValues.back()) < 50;
}

bool FmChannel::NewValueValid(int32_t newValue)
{
  uint32_t currentTime = millis();
  if (!MinMaxValid(newValue) || !ComparedToPreviousValuesValid(newValue))
  {
    startCheckPositiveSignalsAtTime = currentTime + WRONG_SIGNAL_WAIT_TIME_MILLIS;
    stopUpdateUntilTime = startCheckPositiveSignalsAtTime + CHECK_POSITIVE_SIGNALS_TIME_MILLIS;
    return false;
  }
  else if (currentTime > startCheckPositiveSignalsAtTime && currentTime < stopUpdateUntilTime)
  {
    if (!PositiveSignalValid(newValue)) {
      startCheckPositiveSignalsAtTime = currentTime + WRONG_SIGNAL_WAIT_TIME_MILLIS;
      stopUpdateUntilTime = startCheckPositiveSignalsAtTime + CHECK_POSITIVE_SIGNALS_TIME_MILLIS;
    }
    return false;
  }

  return true;
}

void FmChannel::TrySetNewValue(int32_t newValue)
{
  if (NewValueValid(newValue) && CanUpdateValue())
  {
    Value = newValue;
    FmSignalActive = true;
  }
  else {
    FmSignalActive = false;
  }

  AddToPreviousValues(newValue);
}

void FmChannel::ProcessUpdateValueCallback()
{
  UpdateValueCallback();
}
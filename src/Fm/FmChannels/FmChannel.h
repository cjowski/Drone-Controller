#ifndef FM_CHANNEL_H
#define FM_CHANNEL_H

  #include <stdlib.h>
  #include <list>
  #include <stdint.h>
  #include <functional>
  #include <wiring_time.h>

  class FmChannel
  {
    private:
    int32_t Value;
    std::list<int32_t> PreviousValues;
    std::function<void(void)> UpdateValueCallback;
    uint32_t stopUpdateUntilTime = 0;
    uint32_t startCheckPositiveSignalsAtTime = 0;
    const int MAX_PREVIOUS_VALUES_LENGTH = 10;
    const int MAX_ALLOWED_WRONG_VALUES = 1;
    const int ALLOWED_VALUE_DIFFERENCE = 500;
    const int WRONG_SIGNAL_WAIT_TIME_MILLIS = 500;
    const int CHECK_POSITIVE_SIGNALS_TIME_MILLIS = 1000;
    
    void AddToPreviousValues(int32_t value);
    bool CanUpdateValue();
    bool MinMaxValid(int32_t newValue);
    bool ComparedToPreviousValuesValid(int32_t newValue);
    bool PositiveSignalValid(int32_t newValue);

    public:
    static const int MIN_VALUE = 800;
    static const int MAX_VALUE = 2600;
    enum SignalState {
      inactive = 0,
      active = 1,
      restoring = 2
    };
    SignalState FmSignalState;
    FmChannel();
    void AttachUpdateValueCallback(std::function<void(void)> callback);
    int32_t GetValue();
    bool NewValueValid(int32_t newValue);
    void TrySetNewValue(int32_t newValue);
    void ProcessUpdateValueCallback();
  };

#endif
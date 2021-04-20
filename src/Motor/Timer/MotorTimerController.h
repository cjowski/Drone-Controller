#ifndef MOTOR_TIMER_CONTROLLER_H
#define MOTOR_TIMER_CONTROLLER_H

  #include <list>
  #include <HardwareTimer.h>
  #include <PinConfigured.h>
  
  class MotorTimerController
  {
    private:
    std::list<int> ChannelNos;
    const int MAX_CHANNELS_COUNT = 4;

    protected:
    HardwareTimer *Timer;

    public:
    static const uint32_t MAX_PWM_VALUE = 2000;
    static const uint32_t MIN_PWM_VALUE = 1000;
    MotorTimerController() { };
    virtual const uint8_t *CHANNEL_PINS() const = 0;
    virtual int CHANNELS_COUNT() const = 0;
    virtual TIM_TypeDef *TIMER_BASE() const = 0;
    void Setup();
    void SetupChannel(int channelNo);
    void Resume();
    void Refresh();
    void SetChannelValue(int channelNo, uint32_t value);
  };

#endif
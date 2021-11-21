#ifndef BUTTON_H
#define BUTTON_H

  #include <wiring.h>
  #include <WSerial.h>

  class Button
  {
    private:
    uint32_t Pin;
    int PreviousState = 0;
    bool IsButtonOn = false;
    void PrintState();
    std::function<void()> ButtonOnFunction;
    std::function<void()> ButtonOffFunction;

    protected:
    bool DebugMode = false;
    void Loop();

    public:
    Button(uint32_t pin);
    void RegisterButtonOnFunction(std::function<void()> buttonOnFunction);
    void RegisterButtonOffFunction(std::function<void()> buttonOffFunction);
    bool IsOn();

    friend class DroneController;
  };

#endif
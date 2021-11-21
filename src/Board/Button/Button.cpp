#include "Button.h"

Button::Button(uint32_t pin)
{
  Pin = pin;
  ButtonOnFunction = [] () {};
  ButtonOffFunction = [] () {};
}

void Button::RegisterButtonOnFunction(std::function<void()> buttonOnFunction)
{
  ButtonOnFunction = buttonOnFunction;
}

void Button::RegisterButtonOffFunction(std::function<void()> buttonOffFunction)
{
  ButtonOffFunction = buttonOffFunction;
}

bool Button::IsOn()
{
  return IsButtonOn;
}

void Button::Loop()
{
  int currentState = digitalRead(Pin);
  if (currentState == HIGH && PreviousState == LOW) {
    IsButtonOn = !IsButtonOn;

    if (IsButtonOn)
    {
      ButtonOnFunction();
    }
    else
    {
      ButtonOffFunction();
    }

    if (DebugMode)
    {
      PrintState();
    }
  }
  PreviousState = currentState;
}

void Button::PrintState()
{
  String printText = "Button " + String(Pin) + ": ";
  if (IsButtonOn)
  {
    printText += "ON";
  }
  else
  {
    printText += "OFF";
  }
  Serial.println(printText);
}
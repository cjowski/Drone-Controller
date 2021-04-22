#ifndef MOTORS_SERIAL_VALUE_H
#define MOTORS_SERIAL_VALUE_H

  #include "Serial/Value/SerialValue.h"

  class MotorsSerialValue : public SerialValue
  {
    private:
    static const int MOTORS_COUNT = 4;

    long Time;
    int MotorSpeed[MOTORS_COUNT];

    protected:
    bool SerialValuesMatched(std::list<String> serialValues) { return false; };

    public:
    int SERIAL_VALUES_COUNT() const { return MOTORS_COUNT + 1; };
    char SERIAL_VALUE_KEY() const { return 'M'; };
    MotorsSerialValue() { };
    MotorsSerialValue(
      long time,
      int motorSpeed1,
      int motorSpeed2,
      int motorSpeed3,
      int motorSpeed4
    );
    std::list<String> GetPrintStrings();
  };

#endif
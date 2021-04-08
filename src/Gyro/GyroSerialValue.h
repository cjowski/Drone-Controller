#ifndef GYRO_SERIAL_VALUE_H
#define GYRO_SERIAL_VALUE_H

  #include "Serial/Value/SerialValue.h"

  class GyroSerialValue : public SerialValue
  {
    private:
    long Time;
    bool CalibrationDone;
    float Pitch;
    float Roll;
    float Yaw;

    protected:
    bool SerialValuesMatched(std::list<String> serialValues) { return false; };

    public:
    int SERIAL_VALUES_COUNT() const { return 5; };
    char SERIAL_VALUE_KEY() const { return 'G'; };
    GyroSerialValue() { };
    GyroSerialValue(
      long time,
      bool calibrationDone,
      float pitch,
      float roll,
      float yaw
    );
    std::list<String> GetPrintStrings();
  };

#endif
#ifndef UNDEFINED_SERIAL_VALUE_H
#define UNDEFINED_SERIAL_VALUE_H

  #include "SerialValue.h"

  class UndefinedSerialValue : public SerialValue
  {
    private:
    char ReadValueKey;
    std::list<String> Values;

    protected:
    bool SerialValuesMatched(std::list<String> serialValues) { return false; };

    public:
    UndefinedSerialValue(char readValueKey, std::list<String> values);
    int SERIAL_VALUES_COUNT() const { return -1; };
    char SERIAL_VALUE_KEY() const { return 'U'; };
    std::list<String> GetPrintStrings();
    char GetReadValueKey();
    bool Exists();
  };

#endif
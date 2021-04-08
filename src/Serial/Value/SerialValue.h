#ifndef SERIAL_VALUE_H
#define SERIAL_VALUE_H

  #include <list>
  #include <WString.h>
  #include "SerialValueContants.h"

  class SerialValue
  {
    public:
    SerialValue() { };
    virtual int SERIAL_VALUES_COUNT() const = 0;
    virtual char SERIAL_VALUE_KEY() const = 0;
    virtual ~SerialValue() { };
    virtual std::list<String> GetPrintStrings() = 0;
    String ToSerialString();
    bool SerialValueValid(char serialReadKey, std::list<String> serialValues);

    protected:
    virtual bool SerialValuesMatched(std::list<String> serialValues) = 0;

    private:
    bool SerialReadKeyMatched(char serialReadKey);
  };

#endif
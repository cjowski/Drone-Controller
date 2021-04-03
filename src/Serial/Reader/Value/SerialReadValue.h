#ifndef SERIAL_READ_VALUE_H
#define SERIAL_READ_VALUE_H

  #include <WString.h>

  class SerialReadValue
  {
    private:
    const String SERIAL_TEXT_VALUE_EMPTY = "EMPTY";
    char SerialPrintKey;
    String TextValue;

    public:
    SerialReadValue();
    bool Equals(SerialReadValue valueToCompare);
    void SetNewTextValue(char serialPrintKey, String textValue);
    char GetSerialPrintKey();
    String ToString();
  };

#endif
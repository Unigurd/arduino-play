#include <Arduino.h>

#define CHATTERTIME 50

class Pin {
public:
  unsigned char num;
  unsigned char value;
  Pin(unsigned char pin);
  unsigned char digitalReadStable();
  // unsigned char pressed();

private:
  unsigned long lastChange;
  unsigned char stable = 1;
};

Pin::Pin(unsigned char pin) {
  num   = pin;
  value = digitalRead(num);
}

unsigned char Pin::digitalReadStable() {
  unsigned char sameValue = value == digitalRead(num);
  if (sameValue && stable) {
    // Do nothing
  } else if (!sameValue && stable) {
    stable     = !stable;
    lastChange = millis();
  } else if (sameValue && !stable) {
    stable = !stable;
  } else if (!sameValue && !stable) {
    if (lastChange - millis() > CHATTERTIME) {
      value  = !value;
      stable = !stable;
    }
  }

  return value;
}

// unsigned char Pin::pressed() {
//   unsigned char oldVal = value;
//   return (oldVal == HIGH) && (oldVal != digitalReadStable);
// }



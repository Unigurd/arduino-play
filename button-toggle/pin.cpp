#include <Arduino.h>
#include "pin.hpp"

#define CHATTERTIME 50

Pin::Pin(unsigned char pin) {
  num   = pin;
  value = digitalRead(num);
}

// digitalRead, but where the value only changes after the pin has
// remained stable on a value for CHATTERTIME
unsigned char Pin::digitalReadStable() {
  unsigned char sameValue = value == digitalRead(num);

  if (sameValue && stable) {
    // No changes have happened
    // Do nothing

  } else if (!sameValue && stable) {
    // First reading where the pin has changed
    stable     = 0;
    lastChange = millis();
    //Serial.println("(!sameValue && stable)");

  } else if (sameValue && !stable) {
    // The pin has reverted back before CHATTERTIME was over
    stable = 1;
    //Serial.println("(sameValue && !stable)");

  } else if (!sameValue && !stable) {
    // The pin remains at the new value
    //Serial.println("(!sameValue && !stable)");
    if (millis() - lastChange > CHATTERTIME) {
      // The pin has remained at the new value long enough to change
      // Pin.value
      value  = !value;
      stable = 1;
      //Serial.println("(millis() - lastChange > CHATTERTIME)");
    }
  }

  return value;
}

// unsigned char Pin::pressed() {
//   unsigned char oldVal = value;
//   return (oldVal == HIGH) && (oldVal != digitalReadStable);
// }



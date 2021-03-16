#include "vfd.h"
#include "pin.hpp"

#define MINPIN 5
#define MAXPIN 12

#define DIG0 14
#define DIG1 15
#define DIG2 16
#define DIG3 17

#define BUTTON 4

void setup() {
  Serial.begin(9600);
  setupRange(MINPIN, MAXPIN, OUTPUT, LOW);
  setupRange(DIG0, DIG3, OUTPUT, HIGH);
}

void loop() {
  for(byte firstDigit = 0;; ++firstDigit) {
    unsigned long start = millis();
    while (millis() - start < 100) {
      for (byte i = 0; i < 4; ++i) {
        setRange(MINPIN, MAXPIN, LOW);
        /* Add 3 instead of subtract 1 to avoid thinking about underflow */
        switchDigit(((i+3)%4)+DIG0, i+DIG0);
        digitalWriteRange(MINPIN,MAXPIN, snakeEight((firstDigit+i) % 8, 2));
      }
    }
  }
}

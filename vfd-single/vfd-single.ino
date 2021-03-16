#include "vfd.h"

#define MINPIN 5
#define MAXPIN 12

#define DIG0 14
#define DIG1 15
#define DIG2 16
#define DIG3 17

#define SWITCH 4

void setup() {
  Serial.begin(9600);
  setupRange(MINPIN, MAXPIN, OUTPUT, LOW);
  setupRange(DIG0, DIG3, OUTPUT, HIGH);
  pinMode(SWITCH, INPUT_PULLUP);
}

void loop() {
  /* Count up to 9999 */
  for(short digits = 0;; digits = incQuadDigit(digits)) {
    unsigned long start = millis();
    while (millis() - start < 500) {
      for (byte i = 0; i < 4; ++i) {
        byte locked;
        if (!digitalRead(SWITCH)) {
          if (!locked) {
            digits = 0;
            locked = 1;
            start = millis();
          }

          setRange(MINPIN, MAXPIN, LOW);
          /* Add 3 instead of subtract 1 to avoid thinking about underflow */
          switchDigit(((i+3)%4)+DIG0, i+DIG0);
          digitalWriteRange(MINPIN,MAXPIN, vfdNum((byte)((digits >> ((3-i) * 4)&0xf))));
        } else if (locked) {
          setRange(MINPIN, MAXPIN, LOW);
          locked = 0;
        }
      }
    }
  }

  /* Do the snake wave! */
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

/*
   Increment a short where each 4 bytes represents a decimal digit.
   If a digit is 10, shift left and increment the next digit. Continue
   until a non-10 digit is found and then shift all the way back. That
   also zeroes the digits that reached 10.
*/
short incQuadDigit(short qd) {
  byte shift = 0;
  while ((++qd & 0xf) == 10) {
    qd >>= 4;
    shift += 4;
  }
  return qd << shift;
}


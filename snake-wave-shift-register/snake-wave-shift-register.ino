#include "vfd.h"
#include "pin.hpp"
#include "intervalPrinter.hpp"

#define TESTPIN   9

#define DATAPIN  10
#define LATCHPIN 11
#define CLOCKPIN 12

#define DIG0     14
#define DIG1     15
#define DIG2     16
#define DIG3     17

#define POTPIN   18

#define TIME (100UL * 0x20)
#define DIGITS 4
#define SHIFTDELAY 2

void setup() {
  Serial.begin(9600);
  pinMode(POTPIN, INPUT);
  setupRange(DIG0, DIG3, OUTPUT, HIGH);
  setupRange(DATAPIN, CLOCKPIN, OUTPUT, LOW);
}

void loop() {
  char inc = 1;
  int pot  = 0; // Lazyness

  // Iterate through the snake positions
  for(byte firstDigit = 0;; firstDigit += inc) {
    unsigned long start = millis();

    // Hold each snake position for TIME milliseconds
    while ((millis() - start)*pot < TIME) {
      pot = analogRead(POTPIN) - 0x200;
      if (pot < 0) { inc = -1; }
      else {inc = 1;}
      pot = abs(pot);
      if (pot < 4) { pot = 0; }

      // Draw each snake in its own position in each digit
      for (byte i = 0; i < DIGITS; ++i) {
        // Computations up here to minimize time with leds off
        byte snake = snakeEight((firstDigit+i) % 8, 2);
        /* Add DIGITS-1 instead of subtracting 1 to avoid thinking about underflow */
        byte oldDigit = ((i+DIGITS-1)%DIGITS)+DIG0;
        byte newDigit = i+DIG0;

        // Switch leds
        digitalWrite(LATCHPIN, LOW);
        digitalWrite(oldDigit, HIGH);
        shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, snake);
        digitalWrite(newDigit, LOW);
        digitalWrite(LATCHPIN, HIGH);
        delay(SHIFTDELAY);
      }
    }
  }
}

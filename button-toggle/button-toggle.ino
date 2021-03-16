#include "vfd.h"
#include "pin.hpp"

#define MINPIN 5
#define MAXPIN 12

#define DIG0 14
#define DIG1 15
#define DIG2 16
#define DIG3 17

#define BUTTON 4

template <class Message>
class IntervalPrinter {
public:
  unsigned long interval;
  unsigned long startPrint;
  IntervalPrinter(unsigned long i) {
    startPrint = millis();
    interval = i;
  }
  void print(Message x) {
    if (millis() - startPrint >= interval) {
      Serial.println(x);
      startPrint = millis();
    }
  }
};

void setup() {
  Serial.begin(9600);
  setupRange(MINPIN, MAXPIN, OUTPUT, LOW);
  setupRange(DIG0, DIG3, OUTPUT, HIGH);
  pinMode(BUTTON,INPUT_PULLUP);
}

void loop() {
  unsigned char firstDigit = 0;
  Pin pin {BUTTON};
  unsigned char oldVal = pin.digitalReadStable();
  //unsigned char oldVal = digitalRead(BUTTON);
  while (true) {
    if (oldVal != pin.digitalReadStable()) {
    //if (oldVal != digitalRead(BUTTON)) {
      if (oldVal == HIGH) {
        ++firstDigit;
      }
      oldVal = !oldVal;
    }

    for (byte i = 0; i < 4; ++i) {
      setRange(MINPIN, MAXPIN, LOW);
      /* Add 3 instead of subtract 1 to avoid thinking about underflow */
      switchDigit(((i+3)%4)+DIG0, i+DIG0);
      digitalWriteRange(MINPIN,MAXPIN, snakeEight((firstDigit+i) % 8, 2));
    }
  }
}

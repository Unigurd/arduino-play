#include <Arduino.h>
#include "intervalPrinter.hpp"

template <class Message>
IntervalPrinter<Message>::IntervalPrinter(unsigned long i) {
  startPrint = millis();
  interval = i;
}

template <class Message>
void IntervalPrinter<Message>::print(Message x) {
  if (millis() - startPrint >= interval) {
    Serial.println(x);
    startPrint = millis();
  }
}

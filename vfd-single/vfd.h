#ifndef VFD_H
#define VFD_H
#include <Arduino.h>

void setupRange(int min, int max, int io, int current);
byte vfdNum(byte num);
void digitalWriteRange(byte minPin, byte maxPin, byte values);
byte snakeEight(byte num, byte length);
void setRange(byte minPin, byte maxPin, byte val);
void switchDigit(byte oldDigit, byte newDigit);

#endif

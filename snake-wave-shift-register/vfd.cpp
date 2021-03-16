#include "vfd.h"

// Could the ints be bytes?
void setupRange(int min, int max, int io, int current) {
  for (int i = min; i <= max; ++i) {
    pinMode(i, io);
    digitalWrite(i, current);
  }
}


/* Returns a byte representing a drawing of num on a vfd */
/* The order from least to most-significant digit: */
/* Top, top-right, bottom-right, bottom, bottom-left, top-left, middle, dot.  */
/* Returns 0 on input > 0xf */
byte vfdNum(byte num) {
  switch(num) {
  case 0:   return 0b00111111;
  case 1:   return 0b00000110;
  case 2:   return 0b01011011;
  case 3:   return 0b01001111;
  case 4:   return 0b01100110;
  case 5:   return 0b01101101;
  case 6:   return 0b01111101;
  case 7:   return 0b00000111;
  case 8:   return 0b01111111;
  case 9:   return 0b01101111;
  case 0xa: return 0b01110111;
  case 0xb: return 0b01111100;
  case 0xc: return 0b00111001;
  case 0xd: return 0b01011110;
  case 0xe: return 0b01111001;
  case 0xf: return 0b01110001;
  }

  // On input > 0xf:
  return 0;
}

// Sets the digital output pins in the range from minPin to maxPin
// exclusive to val.
void setRange(byte minPin, byte maxPin, byte val) {
  for (byte i = minPin; i <= maxPin; ++i) {
    digitalWrite(i, val);
  }
}


// Write each bit of values to the pins between and including minPin and maxPin.
// Writes the least significant bit to the lowest pin and so forth.
void digitalWriteRange(byte minPin, byte maxPin, byte values) {
  for (byte i = minPin; i <= maxPin; ++i) {
    digitalWrite(i, (values & 1 ? HIGH : LOW));
    values = values >> 1;
  }
}

// Writes each bit of 'values' to pin from LSB to MSB
void digitalWriteSerial(byte pin, byte values) {
  for (byte i = 0; i <= 8; ++i) {
    digitalWrite(pin, (values & 1 ? HIGH : LOW));
    values = values >> 1;
  }
}

/* Draws a 'snake' of the provided length that moves in a figure 8. */
/* num is the placement of the snake in the figure 8. */
byte snakeEight(byte num, byte length) {
  /* Is a switch better? */
  const byte arr[8] = {1, 2, 0x40, 0x10, 8, 4, 0x40, 0x20};
  byte retval = 0;
  for (byte i = length; i > 0; --i) {
    retval   |= arr[(num + i+7) % 8];
  }
  return retval;
}

// Turn on the previously displayed pin oldDigit and turn of the now
// displayed pin newDigit. Note that pins are displayed when they are
// LOW.
void switchDigit(byte oldDigit, byte newDigit) {
  digitalWrite(oldDigit, HIGH);
  digitalWrite(newDigit, LOW);
}

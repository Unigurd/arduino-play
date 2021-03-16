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

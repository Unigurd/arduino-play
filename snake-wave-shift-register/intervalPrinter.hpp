template <class Message>
class IntervalPrinter {
public:
  unsigned long interval;
  unsigned long startPrint;
  IntervalPrinter(unsigned long i);
  void print(Message x);
};

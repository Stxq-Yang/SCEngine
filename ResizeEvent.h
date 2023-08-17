#include "Event.h"
class ResizeEvent:public Event{
public:
  ResizeEvent(){}
  setSize(int width,int high);
private:
  int wdidth,high;
}

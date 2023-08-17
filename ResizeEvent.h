#include "Event.h"
class ResizeEvent:public Event{
public:
  ResizeEvent(){}
  void setSize(int width,int high);
  int getWidth();
  int getHigh();
private:
  int width,high;
}

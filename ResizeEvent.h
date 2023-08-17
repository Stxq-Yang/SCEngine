#include "Event.h"
namespace SCE{
class ResizeEvent:public Event{
public:
  ResizeEvent(){}
  void setSize(int width,int high);
  int getWidth();
  int getHigh();
private:
  int width,high;
}
}

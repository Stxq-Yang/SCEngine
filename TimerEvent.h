#ifndef TIMEREVENT_H
#define TIMEREVENT_H
#include "Event.h"

namespace SCE  {
class TimerEvent:public Event{
public:
  TimerEvent(){
    firstlevel=5;
    EventClassName="TimerEvent";
  }
  long long deptime;
private:
  static int firstlevel;
  static std::string EventClassName;
};
}
#endif

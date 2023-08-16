#ifndef TIMEREVENT_CPP
#define TIMEREVENT_CPP
#include "Timer.cpp"
#include "Event.cpp"
#include "TimerEvent.h"
namespace SCE  {
  int Event::firstlevel = 0;
  std::string Event::EventClassName = "TimerEvent";
}
#endif

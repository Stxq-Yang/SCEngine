#include "Timer.h"
#include "Event.h"
namespace SCE  {
class TimerEvent:public Event{
public:
  using Event::Event;
  long long deptime;
};
}

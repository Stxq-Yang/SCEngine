#include "Event.h"
namespace SCE{
enum MouseEventType{
  LeftButtonDown,
  RightButtonDown,
  MidButtonDown,
  Scroll,
  Move
}
class MouseEvent:public Event{
  public:
  MouseEvent(){}
      void setEventType(MouseEventType type);
      MouseEventType getEventType();
    private:
      MouseEventType eventType;
  };
};
}

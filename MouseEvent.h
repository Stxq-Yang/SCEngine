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
      void setScrollParam(int param);
      int getScrollParam();
    private:
      MouseEventType eventType; 
      int x,y;
      int param;
};
}

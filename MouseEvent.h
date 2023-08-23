#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "Event.h"
namespace SCE{
enum MouseEventType{
  LeftButtonDown,
  RightButtonDown,
  MidButtonDown,
  LeftButtonUp,
  RightButtonUp,
  MidButtonUp,
  Mouse_Scroll,
  Mouse_Move
};
class MouseEvent:public Event{
  public:
      MouseEvent(){
        firstlevel=5;
        EventClassName="MouseEvent";
      }
      void setEventType(MouseEventType type);
      MouseEventType getEventType();
      void setScrollParam(int param);
      int getScrollParam();
      void setPosition(int x,int y);
      int getX();
      int getY();
    private:
      MouseEventType eventType;
      int x,y;
      int param;
};
}
#endif // MOUSEEVENT_H

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
      void setPosition(int x,int y);
      int getX();
      int getY(); 
      int getlastX();
      int getlastY(); 
    private:
      MouseEventType eventType; 
      int x,y,lastx,lasty;
      int param;
};
}

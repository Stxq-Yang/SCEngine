#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "KeyVal.h"
#include "Event.h"
namespace SCE{
  enum KeyEventType{
    KeyDown,
    KeyUp
  };
  class KeyEvent :public Event{
    public:
      KeyEvent(){
        firstlevel=5;
        EventClassName="KeyEvent";
      }
      void setEventType(KeyEventType type);
      KeyEventType getEventType();
      void setKeyCode(SCkey code);
      SCkey getKeyCode();
    private:
      SCkey keyCode;
      KeyEventType eventType;
  };
}
#endif // KEYEVENT_H

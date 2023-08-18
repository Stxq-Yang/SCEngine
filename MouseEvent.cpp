#include "MouseEvent.h"
namespace SCE{
  int MouseEvent::firstlevel = 5;
  std::string TimerEvent::EventClassName = "MouseEvent";
  void KeyEvent::setEventType(MouseEventType type){
    eventType=type;
  }
  MouseEventType KeyEvent::getEventType(){
    return eventType;
  }
}

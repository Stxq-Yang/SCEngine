#include "KeyEvent.h"
namespace SCE{
  void KeyEvent::setEventType(KeyEventType type){
    eventType=type;
  }
  KeyEventType KeyEvent::getEventType(){
    return eventType;
  }
  void KeyEvent::setKeyCode(SCkey code){
    keyCode=code;
  }
  SCkey KeyEvent::getKeyCode(){
    return keyCode;
  }
}

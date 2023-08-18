#include "KeyEvent.h"
namespace SCE{
  int KeyEvent::firstlevel = 5;
  std::string TimerEvent::EventClassName = "KeyEvent";
  void KeyEvent::setEventType(KeyEventType type){
    eventType=type;
  }
  KeyEventType KeyEvent::getEventType(){
    return eventType;
  }
  void KeyEvent::setKayCode(SCKey code){
    keyCode=code
  }
  SCKey KeyEvent::getKeyCodee(){
    return keyCode;
  }
}

#include "KeyEvent.h"
namespace SCE{
  int KeyEvent::firstlevel = 5;
  std::string TimerEvent::EventClassName = "KeyEvent";
  void KeyEvent::setEventType(KeyEventType type);
  KeyEventType KeyEvent::getEventType();
  void KeyEvent::setKayCode(SCKey type);
  SCKey KeyEvent::getKeyCodee();

}

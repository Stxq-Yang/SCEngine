#include "KeyVal.h"
namespace SCE{
  enum KeyEventType{
    KeyDown,
    KeyPress,
    KeyUp
  };
  class KeyEvent{
    public:
      KeyEvent(){}
      void setEventType(KeyEventType type);
      KeyEventType getEventType();
      void setKayCode(SCKey code);
      SCKey getKeyCodee();
    private:
      SCkey keyCode;
      KeyEventType eventType;
  };
}

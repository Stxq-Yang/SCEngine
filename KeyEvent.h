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
      void setKayCode(SCKey type);
      SCKey getKeyCodee();
    private:
      SCkey keyCode;
      KeyEventType eventType;
  };
}

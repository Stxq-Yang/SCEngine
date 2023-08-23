#include "MouseEvent.h"
namespace SCE{
  void MouseEvent::setEventType(MouseEventType type){
    eventType=type;
  }
  MouseEventType MouseEvent::getEventType(){
    return eventType;
  }
  void MouseEvent::setScrollParam(int param){
    this->param=param;
  }
  int MouseEvent::getScrollParam(){
    return param;
  }
  void MouseEvent::setPosition(int x,int y){
    this->x=x;
    this->y=y;
  }
  int MouseEvent::getX(){
    return x;
  }
  int MouseEvent::getY(){
    return y;
  }
}

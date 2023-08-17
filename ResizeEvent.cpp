#include "ResizeEvent.h"
namespace SCE  {
  int ResizeEvent::firstlevel = 5;
  std::string ResizeEvent::EventClassName = "ResizeEvent";
  ResizeEvent::void setSize(int width,int high){
    this->width=width;
    this->high=high;
    
  }
  int ResizeEvent::getWidth(){
    return this->width;
  }
  int ResizeEvent::getHigh(){
    return this->high;
  }
}

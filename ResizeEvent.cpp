#include "ResizeEvent.h"
namespace SCE  {
  int ResizeEvent::firstlevel = 5;
  std::string ResizeEvent::EventClassName = "ResizeEvent";
  ResizeEvent::void setSize(int width,int high){
    this->width=width;
    this->high=high;
    
  }
  ResizeEvent::int getWidth(){
    return this->width;
  }
  ResizeEvent::int getHigh(){
    return this->high;
  }
}

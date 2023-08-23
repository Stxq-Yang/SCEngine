#include "ResizeEvent.h"
namespace SCE  {
  void  ResizeEvent::setSize(int width,int high){
    this->width=width;
    this->high=high;

  }
  int ResizeEvent::getWidth(){
    return this->width;
  }
  int ResizeEvent::getHigh(){
    return this->high;
  }
  #ifdef _WIN32
        HWND ResizeEvent::getWindow(){
          return window;
        }
        void ResizeEvent::setWindow(HWND window){
          this->window=window;
        }
   #elif __linux__
        HWND ResizeEvent::getWindow(){
          return window;
        }
        void ResizeEvent::etWindow(Window window){
          this->window=window;
        }
   #endif
}

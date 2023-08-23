#include "CloseEvent.h"
namespace SCE  {
    #ifdef _WIN32
        HWND CloseEvent::getWindow(){
          return window;
        }
        void CloseEvent::setWindow(HWND window){
          this->window=window;
        }
   #elif __linux__
        HWND CloseEvent::getWindow(){
          return window;
        }
        void CloseEvent::setWindow(Window window){
          this->window=window;
        }
   #endif
}


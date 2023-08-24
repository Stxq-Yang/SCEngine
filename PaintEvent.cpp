#include "PaintEvent.h"
namespace SCE  {
    #ifdef _WIN32
        HWND PaintEvent::getWindow(){
          return window;
        }
        void PaintEvent::setWindow(HWND window){
          this->window=window;
        }
   #elif __linux__
        Window PaintEvent::getWindow(){
          return window;
        }
        void PaintEvent::setWindow(Window window){
          this->window=window;
        }
   #endif
}

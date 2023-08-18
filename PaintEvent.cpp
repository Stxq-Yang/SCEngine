#include "PaintEvent.h"
namespace SCE  {
  int PaintEvent::firstlevel = 3;
  std::string PaintEvent::EventClassName = "PaintEvent";
    #ifdef _WIN32
        HWND PaintEvent::getWindow(){
          return window;
        }
        void PaintEvent::setWindow(HWND window){
          this->window=window;
        }
   #elif __linux__
        HWND PaintEvent::getWindow(){
          return window;
        }
        void PaintEvent::setWindow(Window window){
          this->window=window;
        }
   #endif
}

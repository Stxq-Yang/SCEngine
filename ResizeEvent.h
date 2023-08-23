#ifndef RESIZEEVENT_H
#define RESIZEEVENT_H

#include "Event.h"
#ifdef _WIN32
     #include <windows.h>
#elif __linux__
     #include <X11/Xlib.h>
#endif
namespace SCE{
class ResizeEvent:public Event{
public:
  ResizeEvent(){
    firstlevel=5;
    EventClassName="ResizeEvent";
  }
  void setSize(int width,int high);
  int getWidth();
  int getHigh();
   #ifdef _WIN32
        HWND getWindow();
        void setWindow(HWND window);
   #elif __linux__
        HWND getWindow();
        void setWindow(Window window);
   #endif
private:
  int width,high;
   #ifdef _WIN32
        HWND window;
   #elif __linux__
        Window window;
   #endif
};
}
#endif // RESIZEEVENT_H

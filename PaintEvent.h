#ifndef PAINTEVENT_H
#define PAINTEVENT_H

#include "Event.h"
#ifdef _WIN32
     #include <windows.h>
#elif __linux__
     #include <X11/Xlib.h>
#endif
namespace SCE{
class PaintEvent :public Event{
public:
     PaintEvent(){
         firstlevel=3;
         EventClassName="PaintEvent";
     }
     #ifdef _WIN32
          HWND getWindow();
          void setWindow(HWND window);
     #elif __linux__
          Window getWindow();
          void setWindow(Window window);
     #endif
private:
     #ifdef _WIN32
          HWND window;
     #elif __linux__
          Window window;
     #endif
};
}
#endif // PAINTevent_h

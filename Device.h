#ifndef DEVICE_H
#define DEVICE_H
#include "Event.h"
#include "EventReceiver.h"
#include "Timer.h"
#include "PaintEvent.h"
#include "ResizeEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "CloseEvent.h"

#include <functional>
#include <array>
#ifdef _WIN32
     #include <windows.h>
#elif __linux__
     #include <X11/Xlib.h>
#endif

namespace SCE{
class Driver;
extern int windowsclassId;
class Device{
public:
	Timer timer;
	EventReceiver eventReceiver;
	Driver* driver;
	Device(int width,int height,std::string title);
	void setSize(int width,int height);
	std::array<int,2> getSize();
    std::string gettitle();
    void  settitle(std::string title);
	void  OnPaint(std::function<void(PaintEvent*)> eventFunc);
	void  OnKeyEvent(std::function<void(KeyEvent*)> eventFunc);
	void  OnMouseEvent(std::function<void(MouseEvent*)> eventFunc);
	void  OnCloseEvent(std::function<void(CloseEvent*)> eventFunc);
    #ifdef _WIN32
          int getWinClassId();
          HDC getDC();
          HWND getWindow();
     #elif __linux__
          HWND getWindow();
     #endif
     bool run();
     bool drop();
private:
    int width,height;
    std::string title;
    #ifdef _WIN32
         HWND window;
         static LRESULT CALLBACK WindowProc(HWND hwnd ,UINT uMsg, WPARAM wParam,LPARAM lParam);
         int winClassId;
         HDC deviceContext;
    #elif __linux__
         Window window;
    #endif
};
}
#endif

#include "Device.h"
#include "Driver.h"
#include <GL/gl.h>
#include <iostream>
//Windows 32
namespace SCE{
#ifdef _WIN32
int windowsclassId=0;
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
Device::Device(int width,int height,std::string title){
    // 注册窗口类
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Device::WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = (std::string("WindowClass")+std::to_string(windowsclassId)).c_str();
    this->winClassId=windowsclassId++;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "窗口注册失败！", "错误", MB_ICONERROR | MB_OK);
        exit(-1);
    }

    // 创建窗口
    HWND hwnd = CreateWindowEx(0, (std::string("WindowClass")+std::to_string(this->winClassId)).c_str(), title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "窗口创建失败！", "错误", MB_ICONERROR | MB_OK);
        exit(-1);
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    this->window=hwnd;
    this->deviceContext=GetDC(hwnd);
    this->driver=new Driver(this);
    this->eventReceiver.registerEvent("PaintEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("KeyEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("MouseEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("ResizeEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("CloseEvent",[](Event* event){delete event;});
}
LRESULT CALLBACK Device::WindowProc(HWND hwnd ,UINT uMsg, WPARAM wParam,LPARAM lParam){
    switch (uMsg)
    {
        case WM_CLOSE:{
            // 关闭窗口的事件处理
            CloseEvent *event=new CloseEvent();
            event->setWindow(hwnd);
            sendEvent(event);
            PostQuitMessage(0);
            }
            return 0;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        return 0;
        case WM_PAINT:
            {
                // 绘制窗口的事件处理
                PaintEvent *event=new PaintEvent();
                event->setWindow(hwnd);
                sendEvent(event);
            }
            return 0;

        case WM_SIZE:
            {
                // 窗口大小改变的事件处理
                ResizeEvent *event=new ResizeEvent();
                event->setWindow(hwnd);
                event->setSize(LOWORD(lParam),HIWORD(lParam));
                sendEvent(event);
                // 在这里进行窗口大小改变后的更新操作
            }
            return 0;

        case WM_KEYDOWN:
            {
                // 键盘按下的事件处理
                KeyEvent *event=new KeyEvent();
                event->setEventType(KeyDown);
                event->setKeyCode(static_cast<SCkey>(wParam));
                sendEvent(event);
            }
            return 0;

        case WM_KEYUP:
            {
                KeyEvent *event=new KeyEvent();
                event->setEventType(KeyUp);
                event->setKeyCode(static_cast<SCkey>(wParam));
                sendEvent(event);
            }
            return 0;

        case WM_MOUSEMOVE:
            {
                // 鼠标移动的事件处理
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt;
                pt.x = xPos;
                pt.y = yPos;
                ScreenToClient(hwnd, &pt);
                MouseEvent *event=new MouseEvent();
                event->setPosition(pt.x,pt.y);
                event->setEventType(Mouse_Move);
                sendEvent(event);
            }
            return 0;

        case WM_LBUTTONDOWN:
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt;
                pt.x = xPos;
                pt.y = yPos;
                ScreenToClient(hwnd, &pt);
                MouseEvent *event=new MouseEvent();
                event->setPosition(pt.x,pt.y);
                event->setEventType(LeftButtonDown);
                sendEvent(event);
            }
            return 0;

        case WM_LBUTTONUP:
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt;
                pt.x = xPos;
                pt.y = yPos;
                ScreenToClient(hwnd, &pt);
                MouseEvent *event=new MouseEvent();
                event->setPosition(pt.x,pt.y);
                event->setEventType(LeftButtonUp);
                sendEvent(event);
            }
            return 0;
        case WM_RBUTTONDOWN:
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt;
                pt.x = xPos;
                pt.y = yPos;
                ScreenToClient(hwnd, &pt);
                MouseEvent *event=new MouseEvent();
                event->setPosition(pt.x,pt.y);
                event->setEventType(RightButtonUp);
                sendEvent(event);
            }
            return 0;

        case WM_RBUTTONUP:
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt;
                pt.x = xPos;
                pt.y = yPos;
                ScreenToClient(hwnd, &pt);
                MouseEvent *event=new MouseEvent();
                event->setPosition(pt.x,pt.y);
                event->setEventType(RightButtonUp);
                sendEvent(event);
            }
            return 0;
        // 其他窗口消息处理...
        case WM_MOUSEWHEEL:
        {
            // 鼠标滚轮滚动的事件处理
            int delta = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            // 处理鼠标滚轮滚动事件
            MouseEvent *event=new MouseEvent();
            event->setScrollParam(delta);
            event->setEventType(Mouse_Scroll);
            sendEvent(event);
        }
        return 0;

        case WM_MBUTTONDOWN:
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt;
                pt.x = xPos;
                pt.y = yPos;
                ScreenToClient(hwnd, &pt);
                MouseEvent *event=new MouseEvent();
                event->setPosition(pt.x,pt.y);
                event->setEventType(MidButtonDown);
                sendEvent(event);
            }
            return 0;
        case WM_MBUTTONUP:
            {
                int xPos = GET_X_LPARAM(lParam);
                int yPos = GET_Y_LPARAM(lParam);
                POINT pt;
                pt.x = xPos;
                pt.y = yPos;
                ScreenToClient(hwnd, &pt);
                MouseEvent *event=new MouseEvent();
                event->setPosition(pt.x,pt.y);
                event->setEventType(MidButtonUp);
                sendEvent(event);
            }
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
HDC Device::getDC(){
    return this->deviceContext;
}

void Device::setSize(int width,int height){
    SetWindowPos(window, NULL,CW_USEDEFAULT, CW_USEDEFAULT, width, height,SWP_SHOWWINDOW);
    this->width=width;
    this->height=height;
}
void Device::settitle(std::string title){
    SetWindowText(window, title.c_str());
    this->title=title;
}

bool Device::run(){
    processEvents();
    MSG msg;
    if (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;

}
bool Device::drop(){
    delete driver;
    ReleaseDC(window, deviceContext);
    DestroyWindow(window);
    return true;
}
HWND Device::getWindow(){
    return this->window;
}
int Device::getWinClassId(){
    return this->winClassId;
}
#elif __linux__

Atom Device::WM_DELETE_WINDOW = 0;

Device::Device(int width, int height, std::string title)
    : display(nullptr), window(0), graphicsContext(0), deleteAtom(0), screen(0),
      width(width), height(height), title(title)
{
    display = XOpenDisplay(nullptr);

    if (display == nullptr) {
        std::cerr << "Failed to open X display" << std::endl;
        exit(-1);
    }

    screen = DefaultScreen(display);

    // Create window
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0,
                                 width, height, 0, BlackPixel(display, screen),
                                 WhitePixel(display, screen));

    // Set window properties
    XSetWindowAttributes windowAttributes;
    windowAttributes.event_mask =
        StructureNotifyMask | KeyPressMask | KeyReleaseMask |
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

    XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1);

    XChangeWindowAttributes(display, window, CWEventMask, &windowAttributes);
    XStoreName(display, window, title.c_str());
    XMapWindow(display, window);

    // Create graphics context
    graphicsContext = XDefaultGC(display, screen);

    // Flush initial events
    XSync(display, False);
    
     this->eventReceiver.registerEvent("PaintEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("KeyEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("MouseEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("ResizeEvent",[](Event* event){delete event;});
    this->eventReceiver.registerEvent("CloseEvent",[](Event* event){delete event;});
    driver=new Driver(this);
}

void Device::setSize(int width, int height)
{
    XResizeWindow(display, window, width, height);
    this->width = width;
    this->height = height;
}

void Device::settitle(std::string title)
{
    XStoreName(display, window, title.c_str());
    this->title = title;
}

bool Device::run()
{
    
    XEvent event;
    if(XPending(display)){
	    XNextEvent(display, &event);

	    handleEvent(event, display, window);

	   if (event.type == ClientMessage &&
		static_cast<unsigned long>(event.xclient.data.l[0]) == deleteAtom) {

		 return false;
	}
    }
    return true;
}

bool Device::drop()
{
    if (display != nullptr) {
        XDestroyWindow(display, window);
        XCloseDisplay(display);
        display = nullptr;
        return true;
    }

    return false;
}

void Device::handleEvent(XEvent event, Display* display, Window window) {
    switch (event.type) {
        case ButtonPress:
            if (event.xbutton.button == Button1) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(LeftButtonDown);
                sendEvent(mouseEvent);
            } else if (event.xbutton.button == Button3) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(RightButtonDown);
                sendEvent(mouseEvent);
            } else if (event.xbutton.button == Button2) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(MidButtonDown);
                sendEvent(mouseEvent);
            }else if (event.xbutton.button == Button4) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(Mouse_Scroll);
                mouseEvent->setScrollParam(1);
                sendEvent(mouseEvent);
            }
            else if (event.xbutton.button == Button5) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(Mouse_Scroll);
                mouseEvent->setScrollParam(1);
                sendEvent(mouseEvent);
            }
            break;
        case ButtonRelease:
            if (event.xbutton.button == Button1) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(LeftButtonUp);
                sendEvent(mouseEvent);
            } else if (event.xbutton.button == Button3) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(RightButtonUp);
                sendEvent(mouseEvent);
            } else if (event.xbutton.button == Button2) {
                MouseEvent *mouseEvent = new MouseEvent();
                mouseEvent->setPosition(event.xbutton.x, event.xbutton.y);
                mouseEvent->setEventType(MidButtonUp);
                sendEvent(mouseEvent);
            }
            break;
        case MotionNotify: {
            int xPos = event.xmotion.x;
            int yPos = event.xmotion.y;
            MouseEvent *mouseEvent = new MouseEvent();
            mouseEvent->setPosition(xPos, yPos);
            mouseEvent->setEventType(Mouse_Move);
            sendEvent(mouseEvent);
            break;
        }
        case KeyPress: {
            KeyEvent *keyEvent = new KeyEvent();
            keyEvent->setEventType(KeyDown);
            keyEvent->setKeyCode(static_cast<SCkey>(event.xkey.keycode));
            sendEvent(keyEvent);
            break;
        }
        case KeyRelease: {
            KeyEvent *keyEvent = new KeyEvent();
            keyEvent->setEventType(KeyUp);
            keyEvent->setKeyCode(static_cast<SCkey>(event.xkey.keycode));
            sendEvent(keyEvent);
            break;
        }
        case ConfigureNotify:{
            int width = event.xconfigure.width;
            int height = event.xconfigure.height;
            ResizeEvent *resizeEvent = new ResizeEvent();
            resizeEvent->setWindow(window);
            resizeEvent->setSize(width, height);
            sendEvent(resizeEvent);
            break;
        }
        case DestroyNotify:{
            CloseEvent *event=new CloseEvent();
            event->setWindow(window);
            sendEvent(event);
            break;
        }
        default:
            break;
    }
}
Window Device::getWindow(){
    return this->window;
}
#endif

void  Device::OnPaint(std::function<void(PaintEvent*)> eventFunc){
    eventReceiver.unregisterEvent("PaintEvent",eventReceiver.EventNum("PaintEvent")-1);
    eventReceiver.registerEvent("PaintEvent",[=](Event* event){PaintEvent* nevent=static_cast<PaintEvent*>(event);if (nevent!=nullptr)eventFunc(nevent);});
    eventReceiver.registerEvent("PaintEvent",[](Event* event){delete event;});
}
void  Device::OnKeyEvent(std::function<void(KeyEvent*)> eventFunc){
    eventReceiver.unregisterEvent("KeyEvent",eventReceiver.EventNum("KeyEvent")-1);
    eventReceiver.registerEvent("KeyEvent",[=](Event* event){KeyEvent* nevent=static_cast<KeyEvent*>(event);if (nevent!=nullptr)eventFunc(nevent);});
    eventReceiver.registerEvent("KeyEvent",[](Event* event){delete event;});
}
void  Device::OnMouseEvent(std::function<void(MouseEvent*)> eventFunc){
    eventReceiver.unregisterEvent("MouseEvent",eventReceiver.EventNum("MouseEvent")-1);
    eventReceiver.registerEvent("MouseEvent",[=](Event* event){MouseEvent* nevent=static_cast<MouseEvent*>(event);if (nevent!=nullptr)eventFunc(nevent);});
    eventReceiver.registerEvent("MouseEvent",[](Event* event){delete event;});
}
void  Device::OnCloseEvent(std::function<void(CloseEvent*)> eventFunc){
    eventReceiver.unregisterEvent("CloseEvent",eventReceiver.EventNum("CloseEvent")-1);
    eventReceiver.registerEvent("CloseEvent",[=](Event* event){CloseEvent* nevent=static_cast<CloseEvent*>(event);if (nevent!=nullptr)eventFunc(nevent);});
    eventReceiver.registerEvent("CloseEvent",[=](Event* event){delete event;});
}
void  Device::OnResizeEvent(std::function<void(ResizeEvent*)> eventFunc){
    eventReceiver.unregisterEvent("ResizeEvent",eventReceiver.EventNum("ResizeEvent")-1);
    eventReceiver.registerEvent("ResizeEvent",[=](Event* event){ResizeEvent* nevent=static_cast<ResizeEvent*>(event);if (nevent!=nullptr)eventFunc(nevent);});
    eventReceiver.registerEvent("ResizeEvent",[=](Event* event){delete event;});
}
std::array<int,2> Device::getSize(){
    return {width,height};
}
std::string Device::gettitle(){
    return this->title;
}

}

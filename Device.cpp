#include "Device.h"
#include "Driver.h"
#include <GL/gl.h>
//Windows 32
namespace SCE{
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
            // 窗口销毁的事件处理
            PostQuitMessage(0);
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
                event->setKayCode(static_cast<SCkey>(wParam));
                sendEvent(event);
            }
            return 0;

        case WM_KEYUP:
            {
                KeyEvent *event=new KeyEvent();
                event->setEventType(KeyUp);
                event->setKayCode(static_cast<SCkey>(wParam));
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
std::array<int,2> Device::getSize(){
    return {width,height};
}
std::string Device::gettitle(){
    return this->title;
}
void Device::setSize(int width,int height){
    this->width=width;
    this->height=height;
}
void Device::settitle(std::string title){
    SetWindowText(window, title.c_str());
    this->title=title;
}
int Device::getWinClassId(){
    return this->winClassId;
}
HWND Device::getWindow(){
    return this->window;
}
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
    eventReceiver.registerEvent("CloseEvent",[=](Event* event){PostQuitMessage(0);delete event;});
}
bool Device::run(){
    MSG msg;
    if (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT)
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    processEvents();
    return true;
}
bool Device::drop(){
    delete driver;
    DestroyWindow(window);
    return true;
}
}

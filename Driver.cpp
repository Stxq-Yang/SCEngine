#include "Driver.h"
namespace SCE{
#ifdef _WIN32
Driver::Driver(Device* device){
    this->pdevice=device;
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    // 选择合适的像素格式
    int pixelFormat = ChoosePixelFormat(device->getDC(), &pfd);
    SetPixelFormat(device->getDC(), pixelFormat, &pfd);

    // 创建渲染上下文
    renderContext = wglCreateContext(device->getDC());
}
Driver::~Driver(){
    wglDeleteContext(renderContext);
}

void Driver::Begin(std::array<int,4 >color){
    wglMakeCurrent(pdevice->getDC(), renderContext);
    glClearColor(color[0]/255.0f,color[1]/255.0f,color[2]/255.0f,color[3]/255.0f);
    glClear(GL_COLOR_BUFFER_BIT);

}
void Driver::End(){
    Flush();
    wglMakeCurrent(NULL, NULL);
}
void Driver::Flush(){
    SwapBuffers(pdevice->getDC());
    glFlush();
    pdevice->timer.recordTime();
}
#elif __linux__
Driver::Driver(Device* device) {
    this->pdevice = device;

    static int visualAttribs[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 16,
        GLX_DOUBLEBUFFER,
        None
    };

    XVisualInfo* visualInfo = glXChooseVisual(device->display, DefaultScreen(device->display), visualAttribs);
    this->renderContext = glXCreateContext(device->display, visualInfo, NULL, GL_TRUE);
    XFree(visualInfo);

    glXMakeCurrent(device->display, device->window, renderContext);
}

Driver::~Driver(){
    glXMakeCurrent(pdevice-> display, None, NULL);
    glXDestroyContext(pdevice->display, renderContext);
}

void Driver::Begin(std::array<int,4> color) {
    glClearColor(color[0]/255.0f, color[1]/255.0f, color[2]/255.0f, color[3]/255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Driver::End() {
    Flush();
    glXMakeCurrent(pdevice-> display, None, NULL);
}
void Driver::Flush(){
    glFlush();
    glXSwapBuffers(pdevice->display, pdevice->window);
    pdevice->timer.recordTime();
}
#endif
std::array<int, 2> Driver::ConvertOpenGLPoint(const std::array<int, 2>& openglCoord){
    std::array<int, 2> windowSize=pdevice->getSize();
    int clientWidth = windowSize[0];
    int clientHeight = windowSize[1];

    std::array<int, 2> gdiCoord;
    gdiCoord[0] = openglCoord[0] + clientWidth / 2;
    gdiCoord[1] = -openglCoord[1] + clientHeight / 2;

    return gdiCoord;
}

std::array<int, 2> Driver::ConvertPointToOpenGL(const std::array<int, 2>& gdiCoord){
    std::array<int, 2> windowSize=pdevice->getSize();
    int clientWidth = windowSize[0];
    int clientHeight = windowSize[1];

    std::array<int, 2> openglCoord;
    openglCoord[0] = gdiCoord[0] - clientWidth / 2;
    openglCoord[1] = -gdiCoord[1] + clientHeight / 2;

    return openglCoord;
}
}

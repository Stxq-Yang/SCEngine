#include "Driver.h"
namespace SCE{
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

    // ѡ����ʵ����ظ�ʽ
    int pixelFormat = ChoosePixelFormat(device->getDC(), &pfd);
    SetPixelFormat(device->getDC(), pixelFormat, &pfd);

    // ������Ⱦ������
    renderContext = wglCreateContext(device->getDC());
    wglMakeCurrent(device->getDC(), renderContext);

    // ���� OpenGL ��ʼ��
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // ���������ɫΪ��ɫ
    glClearDepth(1.0f);
}
Driver::~Driver(){
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(renderContext);
}
void Driver::Flush(){
    glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(pdevice->getDC());
    glFlush();
    pdevice->timer.recordTime();
}
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

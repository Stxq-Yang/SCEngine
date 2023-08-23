#ifndef DRIVER_H
#define DRIVER_H
#include "Device.h"
#include <GL/gl.h>
#ifdef _WIN32
#include <gl/wglext.h>
#endif
namespace SCE{
class Driver{
public:
    Driver(Device* device);
    ~Driver();
    Device* pdevice;
    std::array<int, 2> ConvertOpenGLPoint(const std::array<int, 2>& openglCoord);
    void Flush();
    std::array<int, 2> ConvertPointToOpenGL(const std::array<int, 2>& gdiCoord);
private:
    #ifdef _WIN32
    HGLRC renderContext;
    #elif __linux__

    #endif
};
}
#endif // DRIVER_H

#include "Device.h"
#include "Driver.h"
#include <GL\GL.h>
int main(){
    SCE::Device* device=new SCE::Device(400,400,"Hello Window");
    float theta=0.0f;
    while(device->run()){
        device->driver->Begin({0,0,0,255});
        glPushMatrix();
        glRotatef(theta, 0.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f,  -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);

        glEnd();

        glPopMatrix();

        theta += 1.0f;
        device->timer.sleep(1);
        device->driver->End();
    }

    device->drop();
    return 0;
}

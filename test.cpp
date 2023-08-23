#include "Device.h"
#include <GL\GL.h>
int main(){
    SCE::Device* device=new SCE::Device(640,480,"Hello Window");
    while(device->run()){}
    device->drop();
    return 0;
}

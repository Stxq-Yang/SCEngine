#include "Event.h"
namespace SCE{
int Event::firstlevel = 5;

Event::Event(long long time) : dtime(time) {
}

int Event::getFirstLevel() {
    return firstlevel;
}

long long Event::getDetachTime() {
    return dtime;
}

std::string Event::getClassName() {
    return EventClassName;
}
};

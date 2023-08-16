#include "Event.h"
namespace SCE{
int Event::firstlevel = 5;
std::string Event::EventClassName = "BaseEvent";
Event::Event() {
}

int Event::getFirstLevel() {
    return firstlevel;
}

std::string Event::getClassName() {
    return EventClassName;
}
};

#include "Event.h"
namespace SCE{
int Event::firstlevel = 5;
std::string Event::EventClassName = "BaseEvent";

int Event::getFirstLevel() const {
    return firstlevel;
}

std::string Event::getClassName()const {
    return EventClassName;
}
};

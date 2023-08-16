#ifndef EVENT_H
#define EVENT_H

#include <string>
namespace SCE{
class Event {
public:
    Event();

    static int getFirstLevel();

    std::string getClassName();

private:
    static int firstlevel;
    static std::string EventClassName;
};
};
#endif // EVENT_H

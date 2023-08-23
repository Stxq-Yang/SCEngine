#ifndef EVENT_H
#define EVENT_H

#include <string>
namespace SCE{
class Event {
public:
    Event(){}

    int getFirstLevel() const;

    std::string getClassName() const;

protected:
    static int firstlevel;
    static std::string EventClassName;
};
};
#endif // EVENT_H

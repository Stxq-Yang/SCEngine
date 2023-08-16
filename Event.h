#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
public:
    Event(long long time);

    static int getFirstLevel();

    long long getDetachTime();

    std::string getClassName();

private:
    long long dtime;
    static int firstlevel;
    std::string EventClassName;
};

#endif // EVENT_H

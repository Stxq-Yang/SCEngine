#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <functional>
#include <vector>
#include <map>
#include "Event.h"

class EventReceiver {
public:
    EventReceiver();

    void registerEvent(Event* event, std::function<void(Event*)> todo);

    void unregisterEvent(Event* event, int index);

    void unregisterEvent(Event* event);

    void unregisterAll();

    void processEvent(Event* event);

private:
    std::map<std::string, std::vector<std::function<void(Event*)>>> registeredEvent;
};

#endif // EVENTRECEIVER_H

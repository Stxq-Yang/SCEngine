#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <functional>
#include <vector>
#include <map>
#include "Event.h"
namespace SCE{
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
struct eventQueueOrder {
    bool operator()(const Event* event1, const Event* event2) {
        return event1->getFirstLevel() < event2->getFirstLevel();
    }
};

std::priority_queue<Event*, std::vector<Event*>, eventQueueOrder> EventQueue;
std::vector<EventReceiver*> EventBus;

void processEvent();

void sendEvent(Event* event);

void processAllEvent();
};
#endif // EVENTRECEIVER_H

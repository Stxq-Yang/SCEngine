#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include <functional>
#include <vector>
#include <map>
#include <queue>
#include "Event.h"
namespace SCE{
class EventReceiver {
public:
    EventReceiver();

    void registerEvent(Event* event, std::function<void(Event*)> todo);

    void unregisterEvent(Event* event, int index);

    void unregisterEvent(Event* event);

    void registerEvent(std::string classname, std::function<void(Event*)> todo);

    void unregisterEvent(std::string classname, int index);

    void unregisterEvent(std::string classname);

    int EventNum(std::string classname);

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
extern std::priority_queue<Event*, std::vector<Event*>, eventQueueOrder> EventQueue;
extern std::vector<EventReceiver*> EventBus;
void processEvent();

void sendEvent(Event* event);

void processEvents();
};
#endif // EVENTRECEIVER_H

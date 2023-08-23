#include "EventReceiver.h"
namespace SCE{
std::priority_queue<Event*, std::vector<Event*>, eventQueueOrder> EventQueue;
std::vector<EventReceiver*> EventBus;
EventReceiver::EventReceiver() {
    EventBus.push_back(this);
}

void EventReceiver::registerEvent(Event* event, std::function<void(Event*)> todo) {
    registeredEvent[event->getClassName()].push_back(todo);
}

void EventReceiver::unregisterEvent(Event* event, int index) {
    registeredEvent[event->getClassName()].erase(index + registeredEvent[event->getClassName()].begin());
}
void EventReceiver::registerEvent(std::string classname, std::function<void(Event*)> todo) {
    registeredEvent[classname].push_back(todo);
}

void EventReceiver::unregisterEvent(std::string classname, int index) {
    registeredEvent[classname].erase(index + registeredEvent[classname].begin());
}
void EventReceiver::unregisterEvent(std::string classname) {
    registeredEvent.erase(registeredEvent.find(classname));
}

void EventReceiver::unregisterAll() {
    registeredEvent.clear();
}

int EventReceiver::EventNum(std::string classname){
    return registeredEvent[classname].size();
}

void EventReceiver::processEvent(Event* event) {
    auto it = registeredEvent.find(event->getClassName());
    if (it != registeredEvent.end()) {
        for (auto i : it->second)
            i(event);
    }
}
void processEvent() {
    for (auto i : EventBus) {
        i->processEvent(EventQueue.top());
    }
    EventQueue.pop();
}

void sendEvent(Event* event) {
    EventQueue.push(event);
}

void processEvents() {
    while (!EventQueue.empty()) {
        processEvent();
    }
}

};

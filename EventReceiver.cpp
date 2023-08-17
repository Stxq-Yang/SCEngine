#include "EventReceiver.h"
namespace SCE{
EventReceiver::EventReceiver() {
    EventBus.push_back(this);
}

void EventReceiver::registerEvent(Event* event, std::function<void(Event*)> todo) {
    registeredEvent[event->getClassName()].push_back(todo);
}

void EventReceiver::unregisterEvent(Event* event, int index) {
    registeredEvent[event->getClassName()].erase(index + registeredEvent[event->getClassName()].begin());
}

void EventReceiver::unregisterEvent(Event* event) {
    registeredEvent.erase(registeredEvent.find(event->getClassName()));
}

void EventReceiver::unregisterAll() {
    registeredEvent.clear();
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
    delete EventQueue.top();
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

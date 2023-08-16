#include "Timer.cpp"
namespace SCE{
long long Timer::getRealTime() const {
    auto currentTime = Clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
}

double Timer::getTime() const {
    return gtime;
}

void Timer::sleep(unsigned long milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Timer::setTimer(std::function<bool(long long)> trigger, std::function<void()> callbackFunc) {
    timers.push_back({trigger, callbackFunc});
}

void Timer::setSpeed(double newSpeed) {
    speed = newSpeed;
}

void Timer::resetTime() {
    startTime = Clock::now();
    gtime = 0;
}

void Timer::recordTime() {
    lastRecordedTime = Clock::now();
}

double Timer::getDeltaTime() const {
    auto currentTime = Clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastRecordedTime);
    return elapsedTime.count();
}

void* Timer::threadwrapper(void* arg) {
    Timer* ths = static_cast<Timer*>(arg);
    std::this_thread::sleep_for(std::chrono::milliseconds(int(ths->speed * 1000)));
    ths->gtime++;
    for (auto it = ths->timers.begin(); it != ths->timers.end(); it++) {
        if (it->first(ths->gtime))
            it->second();
    }
    return 0;
}
}:

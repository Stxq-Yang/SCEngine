#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <functional>
#include <pthread.h>
#include <thread>

namespace SCE{
class Timer{
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    
    // 构造函数，初始化计时器
    Timer(double speed=1.0f){
        this->speed=speed;
        this->startTime=Clock::now();
        pthread_create(&this->timerthread,NULL,threadwrapper,this);
    }
    
    // 获取当前真实时间（以毫秒为单位）
    static long long getRealTime() const {
        auto currentTime = Clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
    }

    // 获取经过的时间（以秒为单位）
    double getTime() const {
        return gtime;
    }

    // 使程序休眠一定时间（以毫秒为单位）
    void sleep(unsigned long milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    
    // 设置定时器：传入触发条件和回调函数
    void setTimer(std::function<bool(long long)> trigger , std::function<void()> callbackFunc) {
        timers.push_back({trigger,callbackFunc});
    }
    
    // 设置计时速度倍率
    void setSpeed(double newSpeed) {
        speed = newSpeed;
    }

    // 重置计时器
    void resetTime() {
        startTime = Clock::now();
        gtime=0;
    }

    // 记录当前时间点
    void recordTime() {
        lastRecordedTime = Clock::now();
    }

    // 获取上次记录时间到当前时间的时间间隔（以秒为单位）
    double getDeltaTime() const {
        auto currentTime = Clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastRecordedTime);
        return elapsedTime.count();
    }

private:
    // 线程包装函数，用于创建计时器线程
    static void* threadwrapper(void* arg){
        Timer *ths=static_cast<Timer*>(arg);
        std::this_thread::sleep_for(std::chrono::milliseconds(int(ths->speed*1000)));
        ths->gtime++;
        for (auto it=ths->timers.begin();it!=ths->timers.end();it++){
            if (it->first(ths->gtime))
                it->second();
        }
        return 0;
    }
    
    TimePoint startTime; // 计时器开始时间点
    long long gtime; // 经过的时间（以秒为单位）
    double speed; // 计时速度倍率
    TimePoint lastRecordedTime; // 上次记录时间点
    pthread_t timerthread; // 计时器线程
    std::vector<std::pair<std::function<bool(long long)> ,std::function<void()> > > timers; // 定时器触发条件和回调函数的集合
};
}；

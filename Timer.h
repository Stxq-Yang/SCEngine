#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <pthread.h>


namespace SCE{
class Timer{
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    
    Timer(double speed=1.0f); // 构造函数，初始化计时器
    static long long getRealTime() const; // 获取当前真实时间（以毫秒为单位）
    double getTime() const; // 获取经过的时间（以秒为单位）
    void sleep(unsigned long milliseconds); // 使程序休眠一定时间（以毫秒为单位）
    void setTimer(std::function<bool(long long)> trigger , std::function<void()> callbackFunc); // 设置定时器：传入触发条件和回调函数
    void setSpeed(double newSpeed); // 设置计时速度倍率
    void resetTime(); // 重置计时器
    void recordTime(); // 记录当前时间点
    double getDeltaTime() const; // 获取上次记录时间到当前时间的时间间隔（以秒为单位）

private:
    static void* threadwrapper(void* arg); // 线程包装函数，用于创建计时器线程
    
    TimePoint startTime; // 计时器开始时间点
    long long gtime; // 经过的时间（以秒为单位）
    double speed; // 计时速度倍率
    TimePoint lastRecordedTime; // 上次记录时间点
    pthread_t timerthread; // 计时器线程
    std::vector<std::pair<std::function<bool(long long)> ,std::function<void()> > > timers; // 定时器触发条件和回调函数的集合
};
}；
#endif

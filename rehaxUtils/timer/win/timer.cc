#include "timer.h"
#include <windows.h>
#include <unordered_map>

std::unordered_map<UINT_PTR, std::jkunction<void(void)>> winTimerMap;

void RehaxUtilsTimerProc(HWND win, UINT p1, UINT_PTR p2, DWORD p3)
{
    auto tick = winTimerMap[p2];
    tick();
}

rehaxUtils::Timer * rehaxUtils::Timer::startInterval(int intervalMs, std::function<void(void)> tick)
{
    static unsigned int rehaxUtilsTimerId = 4721;
    unsigned int nextId = rehaxUtilsTimerId++;
    HWND win = nullptr;
    auto timerId = SetTimer(win, nextId, intervalMs, (TIMERPROC) RehaxUtilsTimerProc);
    winTimerMap[timerId] = tick;

    Timer * timer = new Timer();
    timer->timer = timerId;
    return timer;
}

void rehaxUtils::Timer::stopTimer(rehaxUtils::Timer * timer)
{
    HWND win = nullptr;
    KillTimer(win, timer->timer);
    winTimerMap.erase(timer->timer);
    timer->timer = 0;
    delete timer;
}

// bool rehaxUtils::Timer::isRunning(rehaxUtils::Timer * timer)
// {
//     return timer.timer != nullptr;
// } 

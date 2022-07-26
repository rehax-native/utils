#include "timer.h"
#import <Foundation/Foundation.h>

rehaxUtils::Timer * rehaxUtils::Timer::startInterval(int intervalMs, std::function<void(void)> tick)
{
  NSTimer * nativeTimer = [NSTimer scheduledTimerWithTimeInterval:(float)intervalMs / 1000.0
                                                          repeats:YES
                                                            block:^ (NSTimer *timer) {
    tick();
  }];
    Timer * timer = new Timer();
    timer->timer = nativeTimer;
    return timer;
}

void rehaxUtils::Timer::stopTimer(rehaxUtils::Timer * timer)
{
    [timer->timer invalidate];
    timer->timer = nullptr;
    delete timer;
}

// bool rehaxUtils::Timer::isRunning(rehaxUtils::Timer * timer)
// {
//     return timer.timer != nullptr;
// }
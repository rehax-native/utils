#pragma once

#include <functional>

namespace rehaxUtils {

class Timer {
public:
    static Timer * startInterval(int intervalMs, std::function<void(void)> tick);
    static void stopTimer(Timer * timer);
    // static bool isRunning(Timer * timer);
private:
    unsigned long timer;
};

}

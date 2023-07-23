#include "SpinLock.h"

Spinlock::Spinlock()
{
    this->speed_time_us = 50;
}
void Spinlock::lock()
{
    while (!try_lock()) {
        usleep(speed_time_us);
    }
}

inline bool Spinlock::try_lock()
{
    return !flag_.test_and_set();
}

void Spinlock::unlock()
{
    flag_.clear();
}

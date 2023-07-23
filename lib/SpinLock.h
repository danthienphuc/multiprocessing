#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <atomic>
#include <unistd.h>

class Spinlock {
public:
    std::atomic_flag flag_{ ATOMIC_FLAG_INIT };
    Spinlock();

    void lock();

    inline bool try_lock();

    void unlock();

    // config
    uint32_t speed_time_us = 50;
};

#endif // SPINLOCK_H
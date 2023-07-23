#ifndef PROCESS_H
#define PROCESS_H

/****************************************************************
 * @brief  Process class
 * @note   The process class is used to create a generic process
 *         with shared memory and a pipe for communication.
*/

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <csignal>
#include <atomic>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "SpinLock.h"

class Process {
public:
    Process(const std::vector<std::string> &args, bool verbose = false);
    ~Process();

    void run();
    bool isAlive() const;
    void wait();

    pid_t pid;
    int exitStatus;
    bool verbose;
    std::vector<std::string> args;

    // shared memory
    std::atomic_flag flag_{ ATOMIC_FLAG_INIT };
    Spinlock spinlock;
    int shm_fd;
    void *shm_ptr;
    size_t shm_size;
    std::string shm_name;
};
#endif // PROCESS_H
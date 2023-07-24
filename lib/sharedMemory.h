// Shared memory class

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

class SharedMemory
{
private:
    int m_shmid;
    size_t m_size;
    void *m_ptr;

public:
    SharedMemory();
    ~SharedMemory();

    bool create(size_t size);
    bool attach(int shmid);
    bool detach();
    bool remove();

    void *ptr() const;
    int shmid() const;
    size_t size() const;
};

#endif // SHARED_MEMORY_H
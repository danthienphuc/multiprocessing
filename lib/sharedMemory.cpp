#include "sharedMemory.h"

using namespace std;

SharedMemory::SharedMemory()
{
    m_shmid = -1;
    m_size = 0;
    m_ptr = NULL;
}

SharedMemory::~SharedMemory()
{
    if (m_ptr != NULL)
    {
        detach();
    }
}

bool SharedMemory::create(size_t size)
{
    m_shmid = shmget(IPC_PRIVATE, size, 0666 | IPC_CREAT);
    if (m_shmid < 0)
    {
        return false;
    }
    m_size = size;
    return true;
}

bool SharedMemory::attach(int shmid)
{
    m_ptr = shmat(shmid, NULL, 0);
    if (m_ptr == (void *)-1)
    {
        return false;
    }
    m_shmid = shmid;
    return true;
}

bool SharedMemory::detach()
{
    if (shmdt(m_ptr) < 0)
    {
        return false;
    }
    m_ptr = NULL;
    return true;
}

void SharedMemory::write(string data)
{
    memcpy(m_ptr, &data, data.size());
}

string SharedMemory::read()
{
    string data;
    memcpy(&data, m_ptr, m_size);
    return data;
}

bool SharedMemory::remove()
{
    if (shmctl(m_shmid, IPC_RMID, NULL) < 0)
    {
        return false;
    }
    m_shmid = -1;
    m_size = 0;
    return true;
}

void *SharedMemory::ptr() const
{
    return m_ptr;
}

int SharedMemory::shmid() const
{
    return m_shmid;
}

size_t SharedMemory::size() const
{
    return m_size;
}
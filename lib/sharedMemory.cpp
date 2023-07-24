#include "sharedMemory.h"

using namespace std;

SharedMemory::SharedMemory(size_t size)
{
    m_shmid = shmget(IPC_PRIVATE, size, 0666 | IPC_CREAT);
    if (m_shmid < 0)
    {
        printf("shmget error\n");
        return;
    }
    m_size = size;
    m_ptr = shmat(m_shmid, NULL, 0);
    if (m_ptr == (void *)-1)
    {
        printf("shmat error\n");
        return;
    }
    printf("shmid: %d\n", m_shmid);
}

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
        shmdt(m_ptr);
    }
    if (m_shmid != -1)
    {
        shmctl(m_shmid, IPC_RMID, NULL);
    }
}

void SharedMemory::write(string data)
{
    memcpy(m_ptr, data.c_str(), m_size);
}

string SharedMemory::read()
{
    string data;
    char *p = (char *)m_ptr;
    data = p;
    cout << "data: " << data << endl;
    return data;
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
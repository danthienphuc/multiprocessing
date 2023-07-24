#include "../lib/sharedMemory.h"
#include <unistd.h>

using namespace std;

int main()
{
    SharedMemory shMem(1024);

    int pid = fork();

    if(pid<0)
    {
        printf("fork error\n");
        return -1;
    }
    else if(pid==0)
    {
        printf("Child process\n");
        int ppid = getppid();
        if(ppid==1)
        {
            printf("%d Parent process of %d is dead\n", ppid, getpid());
        }
        else
        {
            printf("%d Parent process of %d is alive\n", ppid, getpid());
            string email;
            email = shMem.read();
            printf("Email from shmem st %d parent process:\n%s\n", shMem.shmid(), email.c_str());
        }
        printf("Child process exit\n");
        exit(0);
    }
    else
    {
        printf("Parent process\n");
        string email = "This is email from parent process (ShMem)";
        shMem.write(email);

        printf("Parent process exit\n");
    }
}
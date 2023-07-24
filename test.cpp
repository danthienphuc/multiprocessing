// Communication: shared memory
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

using namespace std;

int main()
{
    printf("Multiprocess test app\n");

    // init shared memory
    int shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        printf("shmget error\n");
        return -1;
    }
    printf("shmid: %d\n", shmid);

    // fork
    int pid = fork();

    if (pid < 0)
    {
        printf("fork error\n");
        return -1;
    }
    else if (pid == 0)
    {
        printf("Child process\n");
        // is parent process alive?
        int ppid = getppid();
        if (ppid == 1)
        {
            printf("%d Parent process of %d is dead\n", ppid, getpid());
        }
        else
        {
            printf("%d Parent process of %d is alive\n", ppid, getpid());

            // read email from child process using shared memory
            char *p = (char *)shmat(shmid, NULL, 0);
            if (p == (char *)-1)
            {
                printf("shmat error\n");
                return -1;
            }
            else
            {
                // show email
                printf("Email from parent process:\n%s\n", p);
            }
            printf("Email from parent process: %s\n", p);
            shmdt(p);

        }
        printf("Child process exit\n");
        exit(0);
    }
    else
    {
        printf("Parent process\n");
        // is child process alive?
        int status;
        int ret = waitpid(pid, &status, WNOHANG);
        if (ret == 0)
        {
            printf("%d Child process of %d is alive\n", pid, getpid());

            // send email to child process using shared memory
            char *p = (char *)shmat(shmid, NULL, 0);
            if (p == (char *)-1)
            {
                printf("shmat error\n");
                return -1;
            }
            sprintf(p, "Hello child process, I am your parent process");
            shmdt(p);

            // wait child process exit
            waitpid(pid, &status, 0);
        }
        else
        {
            printf("%d Child process of %d is dead\n", pid, getpid());
        }
        exit(0);
    }
    

    return 0;
}

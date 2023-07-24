// socket between two processes

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
    int fd[2];
    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
    if (ret < 0)
    {
        printf("socketpair error\n");
        return -1;
    }

    int pid = fork();
    if (pid < 0)
    {
        printf("fork error\n");
        return -1;
    }
    else if (pid == 0)
    {
        // child process
        close(fd[0]);
        char buf[1024];
        int n = read(fd[1], buf, sizeof(buf));
        printf("child process read %d bytes\n", n);
        printf("child process read: %s\n", buf);
        write(fd[1], "hello from child process", 25);
        close(fd[1]);
        exit(0);
    }
    else
    {
        // parent process
        close(fd[1]);
        write(fd[0], "hello from parent process", 25);
        char buf[1024];
        int n = read(fd[0], buf, sizeof(buf));
        printf("parent process read %d bytes\n", n);
        printf("parent process read: %s\n", buf);
        close(fd[0]);
    }

    return 0;
}
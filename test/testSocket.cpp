// socket between two processes

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "../lib/fileIO.h"
#include "../lib/sharedMemory.h"

using namespace std;

int main()
{
    // initialize
    FileIO fileIO;
    SharedMemory shMem;
    int pid;

    int fd[2]; // fd is a file descriptor array. fd[0] is for read, fd[1] is for write
    int ret = socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
    if (ret < 0)
    {
        printf("socketpair error\n");
        return -1;
    }
    do
    {
        pid = fork();
        if (pid == 0)
        {
            // child process
            cout << "child process" << endl;
            close(fd[0]);
            char buf[1024]; // buffer for read and write in socket
            int n = read(fd[1], buf, sizeof(buf));
            cout << "child process read: " << buf << endl;
            sleep(3);
            write(fd[1], "I'm alive too", 25);
            close(fd[1]);
            exit(0);
        }
        else
        {
            // parent process
            cout << "parent process" << endl;
            // initialize
            int i = 0;

            // list all files in /data/emails
            string *files = fileIO.listFiles("/data/emails", ".csv");

            // check child process is alive
            int status;
            pid_t ret = waitpid(pid, &status, WNOHANG);
            if (ret == 0)
            {
                cout << "child process is alive" << endl;
            }
            else
            {
                cout << "child process is dead" << endl;
            }
            close(fd[1]);
            sleep(1);
            write(fd[0], "Your parent is alive", 25);
            char buf[1024];
            int n = read(fd[0], buf, sizeof(buf));
            cout << "parent process read: " << buf << endl;
            close(fd[0]);
        }
    } while (pid < 0);

    return 0;
}
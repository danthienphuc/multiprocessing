#include "process.h"

Process::Process(const std::vector<std::string> &args, bool verbose)
{
    this->args = args;
    this->verbose = verbose;
    this->shm_name = "/shm_" + std::to_string(getpid());
    this->shm_size = 4096;
    this->shm_fd = shm_open(shm_name.c_str(), O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        perror("shm_open");
        exit(1);
    }
    if (ftruncate(shm_fd, shm_size) < 0) {
        perror("ftruncate");
        exit(1);
    }
    this->shm_ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    this->flag_.clear();
}

Process::~Process()
{
    if (shm_unlink(shm_name.c_str()) < 0) {
        perror("shm_unlink");
        exit(1);
    }
}

void Process::run()
{
    // create pipe
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        exit(1);
    }
    // fork
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // child
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        printf("Process::Child\n%d\n", pid);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[1]);
        // exec
        char **argv = new char *[args.size() + 1];
        for (size_t i = 0; i < args.size(); i++) {
            argv[i] = new char[args[i].size() + 1];
            strcpy(argv[i], args[i].c_str());
        }
        argv[args.size()] = NULL;
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    } else {
        // parent
        close(pipefd[1]);
        printf("Process::Parent\n%d\n", pid);
        // read from pipe
        char buf[4096];
        ssize_t n;
        while ((n = read(pipefd[0], buf, sizeof(buf))) > 0) {
            if (verbose) {
                std::cout << std::string(buf, n);
            }
        }
        if (n < 0) {
            perror("read");
            exit(1);
        }
        close(pipefd[0]);
    }
}

bool Process::isAlive() const
{

    printf("Process::Alive\n%d\n", pid);
    return waitpid(pid, (int *)&exitStatus, WNOHANG) == 0;
}

void Process::wait()
{
    waitpid(pid, (int *)&exitStatus, 0);
}

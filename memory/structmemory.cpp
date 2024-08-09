#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <csignal>

#define SHM_NAME "/new_shm"

struct SharedMemory
{
    pid_t creator_pid;
    char message[256];
};

void SignalHandler(int signum) {
    std::cout << "Signal received: " << signum << std::endl;
}

int main()
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, sizeof(SharedMemory));

    SharedMemory* shm_ptr = static_cast<SharedMemory*>(mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    pid_t pid = getpid();

    shm_ptr->creator_pid = pid;
    const char* mess = "message yes";
    strncpy(shm_ptr->message, mess, strlen(mess)+1);

    std::cout << mess << std::endl;
    std::cout << shm_ptr->message << std::endl;
    std::cout << shm_ptr->creator_pid << std::endl;

    signal(SIGUSR1, SignalHandler);
    pause();

    std::cout << shm_ptr->message << std::endl;
    std::cout << shm_ptr->creator_pid << std::endl;

    munmap(shm_ptr, sizeof(SharedMemory));
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return 0;
}
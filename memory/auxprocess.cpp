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

int main()
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedMemory));
    SharedMemory* shm_ptr = static_cast<SharedMemory*>(mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    pid_t main_pid = shm_ptr->creator_pid;
    std::cout << "Second process" << std::endl;
    std::cout << main_pid <<std::endl;
    
    std::cout << shm_ptr->message << std::endl;
    const char* mess1 = "aaaaaa";
    strncpy(shm_ptr->message, mess1, strlen(mess1)+1);
    std::cout << strlen(mess1) << std::endl;

    std::cout << shm_ptr->message << std::endl;

    if(kill(main_pid, SIGUSR1) == 0){
        std::cout << "Signal send\n";
    }
    else{
        std::cout << "Error while sending signal\n";
    }

    return 0;






}
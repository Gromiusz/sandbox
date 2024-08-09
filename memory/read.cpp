#include <iostream>
#include <fstream>
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

void readFromFile(SharedMemory* ptr)
{
    std::ifstream file("save.bin", std::ios::in | std::ios::binary);
    if(!file) std::cout << "Error while opening file" << std::endl;
    file.read(reinterpret_cast<char*>(ptr), sizeof(SharedMemory));
    if(!file.good()) std::cout << "Error while writing to file" << std::endl;
}

int main()
{
    SharedMemory shm;
    readFromFile(&shm);
    std::cout << shm.creator_pid << std::endl;
    std::cout << shm.message << std::endl;
}
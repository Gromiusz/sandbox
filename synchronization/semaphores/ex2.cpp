#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct MyBinarySemaphore
{
    pthread_mutex_t bin_semafor;
    unsigned counter;
    static pthread_mutex_t mutex;
    MyBinarySemaphore(unsigned _counter): bin_semafor(PTHREAD_MUTEX_INITIALIZER), counter(_counter) 
    {
        assert(counter<2); 
        if(counter == 0) pthread_mutex_lock(&bin_semafor);
        std::cout << &bin_semafor << std::endl;
    }
};

pthread_mutex_t MyBinarySemaphore::mutex = PTHREAD_MUTEX_INITIALIZER;
MyBinarySemaphore sem1(1), sem2(1);


void P() {
    // pthread_mutex_lock(&MyBinarySemaphore::mutex);
    pthread_mutex_lock(&sem1.bin_semafor);
    pthread_mutex_lock(&sem2.bin_semafor);
    // pthread_mutex_unlock(&MyBinarySemaphore::mutex);
}

void V1() {
    // pthread_mutex_lock(&MyBinarySemaphore::mutex);
    pthread_mutex_unlock(&sem1.bin_semafor);
    // pthread_mutex_unlock(&MyBinarySemaphore::mutex);
}

void V2() {
    // pthread_mutex_lock(&MyBinarySemaphore::mutex);
    pthread_mutex_unlock(&sem2.bin_semafor);
    // pthread_mutex_unlock(&MyBinarySemaphore::mutex);
}

void* funkcja1(void* arg) {

    for(int i=0; i<10; i++)
    {
        P();
        std::cout << "Watek 1 w sekcji krytycznej " << std::endl;
        V1();
        V2();
    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<10; i++)
    {
        P();
        std::cout << "Watek 2 w sekcji krytycznej " << std::endl;;
        V1();
        V2();
    }

    return nullptr;
}

int main() {
    pthread_t watek1, watek2;
    
    pthread_create(&watek1, nullptr, funkcja1, nullptr);
    pthread_create(&watek2, nullptr, funkcja2, nullptr);
    

    pthread_join(watek1, nullptr);
    pthread_join(watek2, nullptr);

    return 0;
}
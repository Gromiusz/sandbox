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
    // static pthread_mutex_t mutex;
    MyBinarySemaphore(unsigned _counter): bin_semafor(PTHREAD_MUTEX_INITIALIZER), counter(_counter) 
    {
        if(counter == 0) pthread_mutex_lock(&bin_semafor);
        std::cout << &bin_semafor << std::endl;
    }
};

MyBinarySemaphore sem(1);

void P1() {
    if(sem.counter <= 1) {
        pthread_mutex_lock(&sem.bin_semafor);
        sem.counter = 0;
    }
    else{
        sem.counter--;
    }
}

void P2() {
    if(sem.counter <= 2) {
        pthread_mutex_lock(&sem.bin_semafor);
        sem.counter = 0;
    }
    else{
        sem.counter -= 2;
    }
}

void V1() {
    if(sem.counter == 0) {
        pthread_mutex_unlock(&sem.bin_semafor);
    }
    sem.counter++;
}

void V3() {
    if(sem.counter == 0) {
        pthread_mutex_unlock(&sem.bin_semafor);
    }
    sem.counter += 3;
}

void* funkcja1(void* arg) {

    for(int i=0; i<10; i++)
    {
        P1();
        std::cout << "Watek 1 w sekcji krytycznej " << sem.counter << std::endl;
        V3();
    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<10; i++)
    {
        P2();
        std::cout << "Watek 2 w sekcji krytycznej " << sem.counter << std::endl;;

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
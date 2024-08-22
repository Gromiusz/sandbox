#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct GeneralSemaphore
{
    pthread_mutex_t bin_semafor;
    static pthread_mutex_t mutex;
    unsigned counter;

    GeneralSemaphore(unsigned _counter) : bin_semafor(PTHREAD_MUTEX_INITIALIZER), counter(_counter) 
    {
        if(counter == 0)
        {
            pthread_mutex_lock(&bin_semafor);
        }
    }
};

pthread_mutex_t GeneralSemaphore::mutex = PTHREAD_MUTEX_INITIALIZER;
GeneralSemaphore sem(3);

void P1()
{
    if(sem.counter <= 1)
    {
        sem.counter = 0;
        pthread_mutex_lock(&sem.bin_semafor);
    }
    else
    {
        sem.counter--;
    }
}

void P2()
{
    if(sem.counter <= 2)
    {
        sem.counter = 0;
        pthread_mutex_lock(&sem.bin_semafor);
    }
    else
    {
        sem.counter -= 2;
    }
}

void P3()
{
    if(sem.counter <= 3)
    {
        sem.counter = 0;
        pthread_mutex_lock(&sem.bin_semafor);
    }
    else
    {
        sem.counter -= 3;
    }
}

void V()
{
    if(sem.counter == 0)
    {
        pthread_mutex_unlock(&sem.bin_semafor);
    }
    sem.counter++;
}

void* funkcja1(void* arg) {

    for(int i=0; i<10; i++)
    {
        PAB();
        std::cout << "Watek 1 w sekcji krytycznej A:" << semA.counter << " B: " << semB.counter << std::endl;
        VAB();
    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<10; i++)
    {
        PB2();
        std::cout << "Watek 2 w sekcji krytycznej A:" << semA.counter << " B: " << semB.counter << std::endl;
        VAB();

    }

    return nullptr;
}

int main() {
    pthread_t watek1, watek2;
    
    pthread_create(&watek1, nullptr, funkcja1, nullptr);
    pthread_create(&watek2, nullptr, funkcja2, nullptr);
    

    pthread_join(watek1, nullptr);
    pthread_join(watek2, nullptr);

    pthread_mutex_destroy(&semA.bin_semafor);
    pthread_mutex_destroy(&semB.bin_semafor);


    return 0;
}
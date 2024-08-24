#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct MySemaphore
{
    pthread_mutex_t bin_sem1;
    pthread_mutex_t bin_sem2;
    pthread_mutex_t bin_sem12;
    unsigned counter1;
    unsigned counter2;
    unsigned waiting1;
    unsigned waiting2;
    unsigned waiting12;
    pthread_mutex_t mutex;
    MySemaphore(unsigned _counter1, unsigned _counter2): bin_sem1(PTHREAD_MUTEX_INITIALIZER), bin_sem2(PTHREAD_MUTEX_INITIALIZER), mutex(PTHREAD_MUTEX_INITIALIZER), counter1(_counter1), counter2(_counter2), waiting1(0), waiting2(0)
    {
        pthread_mutex_lock(&bin_sem1);
        pthread_mutex_lock(&bin_sem2);
        pthread_mutex_lock(&bin_sem12);
    }
    ~MySemaphore()
    {
        pthread_mutex_destroy(&bin_sem1);
        pthread_mutex_destroy(&bin_sem2);
        pthread_mutex_destroy(&bin_sem12);
        pthread_mutex_destroy(&mutex);
    }
};

MySemaphore sem(1, 4);

void P() {
    pthread_mutex_lock(&sem.mutex);
    if(sem.counter1 == 0 || sem.counter2 == 0) 
    {
        sem.waiting12++;
        pthread_mutex_unlock(&sem.mutex);
        pthread_mutex_lock(&sem.bin_sem12);
        sem.waiting12--;
    }
    sem.counter1--;
    sem.counter2--;
    pthread_mutex_unlock(&sem.mutex);
}

void V1() {
    pthread_mutex_lock(&sem.mutex);
    sem.counter1++;
    if(sem.waiting12 > 0 && sem.counter2 > 0)
    {
        pthread_mutex_unlock(&sem.bin_sem12);
        pthread_mutex_lock(&sem.mutex);
    }
    pthread_mutex_unlock(&sem.mutex);
}

void V2() {
    pthread_mutex_lock(&sem.mutex);
    sem.counter2++;
    if(sem.waiting12 > 0 && sem.counter1 > 0)
    {
        pthread_mutex_unlock(&sem.bin_sem12);
        pthread_mutex_lock(&sem.mutex);
    }
    pthread_mutex_unlock(&sem.mutex);
}

void* funkcja1(void* arg) {

    for(int i=0; i<3; i++)
    {
        P();
        std::cout << "Watek 1 w sekcji krytycznej " << std::endl;
        V2();
    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<3; i++)
    {
        std::cout << "Watek 2 w sekcji krytycznej " << std::endl;;
        V1();
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
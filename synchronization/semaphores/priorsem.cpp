#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct PrioritySemaphore
{
    pthread_mutex_t lowprior;
    pthread_mutex_t highprior;
    pthread_mutex_t mutex;
    unsigned counter;
    unsigned lowprior_waiting;
    unsigned highprior_waiting;
    unsigned change;

    PrioritySemaphore(unsigned _counter) : lowprior(PTHREAD_MUTEX_INITIALIZER), highprior(PTHREAD_MUTEX_INITIALIZER), mutex(PTHREAD_MUTEX_INITIALIZER), counter(_counter), lowprior_waiting(0), highprior_waiting(0), change(0)
    {
        assert(_counter <= 1);
        pthread_mutex_lock(&lowprior);
        pthread_mutex_lock(&highprior);
    }
    ~PrioritySemaphore()
    {
        pthread_mutex_destroy(&mutex);
        pthread_mutex_destroy(&lowprior);
        pthread_mutex_destroy(&highprior);
    }

    void p(pthread_mutex_t& sem) { pthread_mutex_lock(&sem); }
    void v(pthread_mutex_t& sem) { pthread_mutex_unlock(&sem); }

    void p(bool has_priority)
    {
        p(mutex);

        if(change%2) {has_priority = !has_priority;}

        if(counter == 0)
        {
            if(has_priority)
            {
                highprior_waiting++;
                v(mutex);
                p(highprior);
                highprior_waiting--;
            }
            else
            {
                highprior_waiting++;
                v(mutex);
                p(highprior);
                highprior_waiting--;
            }
        }
        counter--;

        v(mutex);
    }

    void v()
    {
        p(mutex);
        counter = 1;
        if(highprior_waiting > 0 && !(change%2))
        {
            v(highprior);
            p(mutex);
        }
        else if(lowprior_waiting > 0)
        {
            v(lowprior);
            p(mutex);
        }
        if(highprior_waiting > 0 && !(change%2))
        {
            v(highprior);
            p(mutex);
        }
        change++;
        v(mutex);
    }
};

PrioritySemaphore sem(1);


void* funkcja1(void* arg) {

    for(int i=0; i<10; i++)
    {
        sem.p(1);
        std::cout << "Watek 1 w sekcji krytycznej" << std::endl;
        sem.v();
    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<10; i++)
    {
        sem.p(0);
        std::cout << "Watek 2 w sekcji krytycznej" << std::endl;
        sem.v();

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
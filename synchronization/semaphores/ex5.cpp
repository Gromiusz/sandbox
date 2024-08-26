#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct GeneralSemaphore
{
    pthread_mutex_t sem1;
    pthread_mutex_t sem2;
    pthread_mutex_t sem3;
    pthread_mutex_t mutex;
    unsigned counter;
    unsigned waiting1;
    unsigned waiting2;
    unsigned waiting3;

    GeneralSemaphore(unsigned _counter) : sem1(PTHREAD_MUTEX_INITIALIZER), sem2(PTHREAD_MUTEX_INITIALIZER), sem3(PTHREAD_MUTEX_INITIALIZER), mutex(PTHREAD_MUTEX_INITIALIZER), counter(_counter), waiting1(0), waiting2(0), waiting3(0)
    {
        pthread_mutex_lock(&sem1);
        pthread_mutex_lock(&sem2);
        pthread_mutex_lock(&sem3);
    }
    ~GeneralSemaphore()
    {
        pthread_mutex_destroy(&sem1);
        pthread_mutex_destroy(&sem2);
        pthread_mutex_destroy(&sem3);
    }

    void p(pthread_mutex_t& sem) { pthread_mutex_lock(&sem); }
    void v(pthread_mutex_t& sem) { pthread_mutex_unlock(&sem); }

    void P1()
    {
        p(mutex);
        if(counter == 0 || (counter < 2 && waiting2 > 0) || (counter < 3 && waiting3 > 0))
        {
            waiting1++;
            v(mutex);
            p(sem1);
            waiting1--;
        }
        counter--;
        v(mutex);
    }

    void P2()
    {
        p(mutex);
        if(counter < 2 || (counter < 3 && waiting3 > 0))
        {
            waiting2++;
            v(mutex);
            p(sem2);
            waiting2--;
        }
        counter -= 2;
        v(mutex);
    }

    void P3()
    {
        p(mutex);
        if(counter < 3)
        {
            waiting3++;
            v(mutex);
            p(sem3);
            waiting3--;
        }
        counter -= 3;
        v(mutex);
    }

    void V()
    {
        p(mutex);
        counter++;
        if(waiting3 > 0 && counter == 3)
        {
            v(sem3);
            p(mutex);
        }
        else if(waiting2 > 0 && counter == 2)
        {
            v(sem2);
            p(mutex);
        }
        else if(waiting1 > 0)
        {
            v(sem1);
            p(mutex);
        }
        v(mutex);
    }
};

GeneralSemaphore sem(3);

void* funkcja1(void* arg) {

    for(int i=0; i<10; i++)
    {
        sem.P3();
        std::cout << "Watek 1 w sekcji krytycznej" << std::endl;
        sem.V();
        sem.V();
        sem.V();
    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<10; i++)
    {
        sem.P1();
        std::cout << "Watek 2 w sekcji krytycznej" << std::endl;
        sem.V();
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
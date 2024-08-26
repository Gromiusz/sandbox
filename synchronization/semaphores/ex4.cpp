#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct CoupledSemaphore
{
    pthread_mutex_t semA;
    pthread_mutex_t semB;
    pthread_mutex_t semAB;
    pthread_mutex_t mutex;

    unsigned counterA;
    unsigned counterB;

    unsigned waitingA;
    unsigned waitingB;
    unsigned waitingAB;

    CoupledSemaphore(unsigned _counterA, unsigned _counterB): semA(PTHREAD_MUTEX_INITIALIZER), semB(PTHREAD_MUTEX_INITIALIZER), semAB(PTHREAD_MUTEX_INITIALIZER), mutex(PTHREAD_MUTEX_INITIALIZER), counterA(_counterA), counterB(_counterB), waitingA(0), waitingB(0), waitingAB(0)
    {
        pthread_mutex_lock(&semA);
        pthread_mutex_lock(&semB);
        pthread_mutex_lock(&semAB);
    }
    ~CoupledSemaphore()
    {
        pthread_mutex_destroy(&semA);
        pthread_mutex_destroy(&semB);
        pthread_mutex_destroy(&semAB);
        pthread_mutex_destroy(&mutex);
    }

    void p(pthread_mutex_t& sem) { pthread_mutex_lock(&sem); }
    void v(pthread_mutex_t& sem) { pthread_mutex_unlock(&sem); }

    void PA2()
    {
        p(mutex);
        if(counterA < 2)
        {
            waitingA++;
            v(mutex);
            p(semA);
            waitingA--;
        }
        counterA -= 2;
        v(mutex);
    }

    void PB2()
    {
        p(mutex);
        if(counterB < 2)
        {
            waitingB++;
            v(mutex);
            p(semB);
            waitingB--;
        }
        counterB -= 2;
        v(mutex);
    }

    void PAB()
    {
        p(mutex);
        if(counterA == 0 || counterB == 0)
        {
            waitingAB++;
            v(mutex);
            p(semAB);
            waitingAB--;
        }
        counterA--;
        counterB--;
        v(mutex);
    }

    void VA2()
    {
        p(mutex);
        if(waitingAB > 0 && counterB > 0)
        {
            v(semAB);
            p(mutex);
        }
        else if(waitingA>0)
        {
            v(semA);
            p(mutex);
        }
        v(mutex);
    }

    void VB2()
    {
        p(mutex);
        if(waitingAB > 0 && counterA > 0)
        {
            v(semAB);
            p(mutex);
        }
        else if(waitingB>0)
        {
            v(semB);
            p(mutex);
        }
        v(mutex);
    }

    void VAB()
    {
        p(mutex);
        if(waitingAB > 0)
        {
            v(semAB);
            p(mutex);
        }
        else if (waitingA > 0 && counterA == 1)
        {
            v(semA);
            p(mutex);
        }
        else if (waitingB > 0 && counterB == 1)
        {
            v(semB);
            p(mutex);
        }

        v(mutex);
    }

};

CoupledSemaphore sem(1, 1);


void* funkcja1(void* arg) {

    for(int i=0; i<10; i++)
    {
        
        std::cout << "Watek 1 w sekcji krytycznej A:" << sem.counterA << " B: " << sem.counterB << std::endl;

    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<10; i++)
    {

        std::cout << "Watek 2 w sekcji krytycznej A:" << sem.counterA << " B: " << sem.counterB << std::endl;
        

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

// struct GeneralSemaphore
// {
//     pthread_mutex_t bin_semafor;
//     static pthread_mutex_t mutex;
//     unsigned counter;

//     GeneralSemaphore(unsigned _counter) : bin_semafor(PTHREAD_MUTEX_INITIALIZER), counter(_counter) 
//     {
//         if(counter == 0)
//         {
//             pthread_mutex_lock(&bin_semafor);
//         }
//     }
// };

// pthread_mutex_t GeneralSemaphore::mutex = PTHREAD_MUTEX_INITIALIZER;
// GeneralSemaphore semA(1), semB(1);

// void PA2()
// {
//     pthread_mutex_lock(&GeneralSemaphore::mutex);
//     if(semA.counter <=2){
//         semA.counter = 0;
//         pthread_mutex_unlock(&GeneralSemaphore::mutex);
//         pthread_mutex_lock(&semA.bin_semafor);
//     }
//     else {
//         semA.counter -= 2;
//     }
//     std::cout << "Po operacji PA2 A:" << semA.counter << " B: " << semB.counter << std::endl;
//     pthread_mutex_unlock(&GeneralSemaphore::mutex);
// }

// void PB2()
// {
//     pthread_mutex_lock(&GeneralSemaphore::mutex);
//     if(semB.counter <=2){
//         semB.counter = 0;
//         pthread_mutex_unlock(&GeneralSemaphore::mutex);
//         pthread_mutex_lock(&semB.bin_semafor);
//     }
//     else {
//         semB.counter -= 2;
//     }
//     std::cout << "Po operacji PB2 A:" << semA.counter << " B: " << semB.counter << std::endl;
//     pthread_mutex_unlock(&GeneralSemaphore::mutex);
// }

// void VA2()
// {
//     pthread_mutex_lock(&GeneralSemaphore::mutex);
//     if(semA.counter == 0){
//         pthread_mutex_unlock(&semA.bin_semafor);
//     }
//     semA.counter += 2;
//     std::cout << "Po operacji VA2 A:" << semA.counter << " B: " << semB.counter << std::endl;
//     pthread_mutex_unlock(&GeneralSemaphore::mutex);
// }

// void VB2()
// {
//     pthread_mutex_lock(&GeneralSemaphore::mutex);
//     if(semB.counter == 0){
//         pthread_mutex_unlock(&semB.bin_semafor);
//     }
//     semB.counter += 2;
//     std::cout << "Po operacji PB2 A:" << semA.counter << " B: " << semB.counter << std::endl;
//     pthread_mutex_unlock(&GeneralSemaphore::mutex);
// }

// void PAB()
// {
//     pthread_mutex_lock(&GeneralSemaphore::mutex);
//     if(semA.counter <= 1){
//         semA.counter = 0;
//         pthread_mutex_unlock(&GeneralSemaphore::mutex);
//         pthread_mutex_lock(&semA.bin_semafor);
//     }
//     else {
//         semA.counter -= 1;
//     }
//     if(semB.counter <= 1){
//         semB.counter = 0;
//         pthread_mutex_unlock(&GeneralSemaphore::mutex);
//         pthread_mutex_lock(&semB.bin_semafor);
//     }
//     else {
//         semB.counter -= 1;
//     }
//     std::cout << "Po operacji PAB A:" << semA.counter << " B: " << semB.counter << std::endl;
//     pthread_mutex_unlock(&GeneralSemaphore::mutex);
// }

// void VAB()
// {
//     pthread_mutex_lock(&GeneralSemaphore::mutex);
//     if(semA.counter == 0){
//         pthread_mutex_unlock(&semA.bin_semafor);
//     }
//     semA.counter += 1;
//     if(semB.counter == 0){
//         pthread_mutex_unlock(&semB.bin_semafor);
//     }
//     semB.counter += 1;
//     std::cout << "Po operacji VAB A:" << semA.counter << " B: " << semB.counter << std::endl;
//     pthread_mutex_unlock(&GeneralSemaphore::mutex);
// }


// void* funkcja1(void* arg) {

//     for(int i=0; i<10; i++)
//     {
//         PAB();
//         std::cout << "Watek 1 w sekcji krytycznej A:" << semA.counter << " B: " << semB.counter << std::endl;
//     }

//     return nullptr;
// }

// void* funkcja2(void* arg) {

//     for(int i=0; i<10; i++)
//     {
//         std::cout << "Watek 2 w sekcji krytycznej A:" << semA.counter << " B: " << semB.counter << std::endl;
//         VAB();

//     }

//     return nullptr;
// }

// int main() {
//     pthread_t watek1, watek2;
    
//     pthread_create(&watek1, nullptr, funkcja1, nullptr);
//     pthread_create(&watek2, nullptr, funkcja2, nullptr);
    

//     pthread_join(watek1, nullptr);
//     pthread_join(watek2, nullptr);

//     pthread_mutex_destroy(&semA.bin_semafor);
//     pthread_mutex_destroy(&semB.bin_semafor);


//     return 0;
// }
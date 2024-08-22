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
GeneralSemaphore semA(3), semB(5);

void PA2()
{
    pthread_mutex_lock(&GeneralSemaphore::mutex);
    if(semA.counter <=2){
        semA.counter = 0;
        pthread_mutex_lock(&semA.bin_semafor);
    }
    else {
        semA.counter -= 2;
    }
    std::cout << "Po operacji PA2 A:" << semA.counter << " B: " << semB.counter << std::endl;
    pthread_mutex_unlock(&GeneralSemaphore::mutex);
}

void PB2()
{
    pthread_mutex_lock(&GeneralSemaphore::mutex);
    if(semB.counter <=2){
        semB.counter = 0;
        pthread_mutex_lock(&semB.bin_semafor);
    }
    else {
        semB.counter -= 2;
    }
    std::cout << "Po operacji PB2 A:" << semA.counter << " B: " << semB.counter << std::endl;
    pthread_mutex_unlock(&GeneralSemaphore::mutex);
}

void VA2()
{
    pthread_mutex_lock(&GeneralSemaphore::mutex);
    if(semA.counter == 0){
        pthread_mutex_unlock(&semA.bin_semafor);
    }
    semA.counter += 2;
    std::cout << "Po operacji VA2 A:" << semA.counter << " B: " << semB.counter << std::endl;
    pthread_mutex_unlock(&GeneralSemaphore::mutex);
}

void VB2()
{
    pthread_mutex_lock(&GeneralSemaphore::mutex);
    if(semB.counter == 0){
        pthread_mutex_unlock(&semB.bin_semafor);
    }
    semB.counter += 2;
    std::cout << "Po operacji PB2 A:" << semA.counter << " B: " << semB.counter << std::endl;
    pthread_mutex_unlock(&GeneralSemaphore::mutex);
}

void PAB()
{
    pthread_mutex_lock(&GeneralSemaphore::mutex);
    if(semA.counter <= 1){
        semA.counter = 0;
        pthread_mutex_lock(&semA.bin_semafor);
    }
    else {
        semA.counter -= 1;
    }
    if(semB.counter <= 1){
        semB.counter = 0;
        pthread_mutex_lock(&semB.bin_semafor);
    }
    else {
        semB.counter -= 1;
    }
    std::cout << "Po operacji PAB A:" << semA.counter << " B: " << semB.counter << std::endl;
    pthread_mutex_unlock(&GeneralSemaphore::mutex);
}

void VAB()
{
    pthread_mutex_lock(&GeneralSemaphore::mutex);
    if(semA.counter == 0){
        pthread_mutex_unlock(&semA.bin_semafor);
    }
    semA.counter += 1;
    if(semB.counter == 0){
        pthread_mutex_unlock(&semB.bin_semafor);
    }
    semB.counter += 1;
    std::cout << "Po operacji VAB A:" << semA.counter << " B: " << semB.counter << std::endl;
    pthread_mutex_unlock(&GeneralSemaphore::mutex);
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
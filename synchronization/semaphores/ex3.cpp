#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct GeneralSemaphore
{
    pthread_mutex_t bin_sem1;
    pthread_mutex_t bin_sem2;
    pthread_mutex_t mutex;
    unsigned counter;
    unsigned waiting1;
    unsigned waiting2;

    GeneralSemaphore(unsigned _counter1, unsigned _counter2): bin_sem1(PTHREAD_MUTEX_INITIALIZER), bin_sem2(PTHREAD_MUTEX_INITIALIZER), mutex(PTHREAD_MUTEX_INITIALIZER), counter1(_counter1), counter2(_counter2), waiting1(0), waiting2(0)
    {
        pthread_mutex_lock(&bin_sem1);
        pthread_mutex_lock(&bin_sem2);
    }
    ~GeneralSemaphore()
    {
        pthread_mutex_destroy(&bin_sem1);
        pthread_mutex_destroy(&bin_sem2);
        pthread_mutex_destroy(&mutex);
    }

    void p(pthread_mutex_t& sem) { pthread_mutex_lock(&sem); }
    void v(pthread_mutex_t& sem) { pthread_mutex_unlock(&sem); }

public:
    void P1()
    {
        p(mutex);
        if(counter == 0 || (counter == 1 && waiting2 > 0))
        {
            waiting1++;
            v(mutex);
            p(bin_sem1);
            waiting1--;
        }
        counter--;

        v(mutex);
    }

    void P2()
    {
        p(mutex);
        if(counter < 2)
        {
            
        }

        v(mutex);
    }

    void V1()
    {
        p(mutex);
        

        v(mutex);
    }

    void V3()
    {
        p(mutex);
        

        v(mutex);
    }
};


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

// #include <iostream>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>
// #include <memory>
// #include <cstdlib>
// #include <cassert>

// struct MyBinarySemaphore
// {
//     pthread_mutex_t bin_semafor;
//     unsigned counter;
//     // static pthread_mutex_t mutex;
//     MyBinarySemaphore(unsigned _counter): bin_semafor(PTHREAD_MUTEX_INITIALIZER), counter(_counter) 
//     {
//         if(counter == 0) pthread_mutex_lock(&bin_semafor);
//         std::cout << &bin_semafor << std::endl;
//     }
// };

// MyBinarySemaphore sem(1);

// void P1() {
//     if(sem.counter <= 1) {
//         pthread_mutex_lock(&sem.bin_semafor);
//         sem.counter = 0;
//     }
//     else{
//         sem.counter--;
//     }
// }

// void P2() {
//     if(sem.counter <= 2) {
//         pthread_mutex_lock(&sem.bin_semafor);
//         sem.counter = 0;
//     }
//     else{
//         sem.counter -= 2;
//     }
// }

// void V1() {
//     if(sem.counter == 0) {
//         pthread_mutex_unlock(&sem.bin_semafor);
//     }
//     sem.counter++;
// }

// void V3() {
//     if(sem.counter == 0) {
//         pthread_mutex_unlock(&sem.bin_semafor);
//     }
//     sem.counter += 3;
// }

// void* funkcja1(void* arg) {

//     for(int i=0; i<10; i++)
//     {
//         P1();
//         std::cout << "Watek 1 w sekcji krytycznej " << sem.counter << std::endl;
//         V3();
//     }

//     return nullptr;
// }

// void* funkcja2(void* arg) {

//     for(int i=0; i<10; i++)
//     {
//         P2();
//         std::cout << "Watek 2 w sekcji krytycznej " << sem.counter << std::endl;;

//     }

//     return nullptr;
// }

// int main() {
//     pthread_t watek1, watek2;
    
//     pthread_create(&watek1, nullptr, funkcja1, nullptr);
//     pthread_create(&watek2, nullptr, funkcja2, nullptr);
    

//     pthread_join(watek1, nullptr);
//     pthread_join(watek2, nullptr);

//     return 0;
// }
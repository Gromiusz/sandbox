#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <cassert>

struct MySemaphore
{
    pthread_mutex_t bin_sem;
    unsigned counter;
    unsigned waiting;

    MySemaphore(unsigned _counter): bin_sem(PTHREAD_MUTEX_INITIALIZER), counter(_counter), waiting(0)
    {
        pthread_mutex_lock(&bin_sem);
    }
    ~MySemaphore() {
        pthread_mutex_destroy(&bin_sem);
    }

    void p() {pthread_mutex_lock(&bin_sem);}
    void v() {pthread_mutex_unlock(&bin_sem);}
};


struct CoupledSemaphore
{
    MySemaphore& sem1;
    MySemaphore& sem2;
    pthread_mutex_t mutex;

    CoupledSemaphore(MySemaphore& _sem1, MySemaphore& _sem2): sem1(_sem1), sem2(_sem2), mutex(PTHREAD_MUTEX_INITIALIZER)
    {}
    ~CoupledSemaphore() {
        pthread_mutex_destroy(&mutex);
    }

    void p() {pthread_mutex_lock(&mutex);}
    void v() {pthread_mutex_unlock(&mutex);}
};

MySemaphore firstSemaphore(1), secondSemaphore(2);
CoupledSemaphore csem(firstSemaphore, secondSemaphore);


void P(MySemaphore& sem) {
    csem.p();
    if(sem.counter == 0) { 
        sem.waiting++; 
        csem.v(); 
        sem.p(); 
        sem.waiting--; 
    }
    sem.counter--;
    csem.v();
}

void V1V2() {
    csem.p();
    csem.sem1.counter += 1;
    csem.sem2.counter += 2;
    if(csem.sem1.waiting>0) { 
        csem.sem1.v(); 
        csem.p(); 
    }
    if(csem.sem2.waiting>0) { 
        csem.sem2.v(); 
        csem.p(); 
    }
    csem.v();
}

void V2V1() {
    csem.p();
    csem.sem1.counter += 2;
    csem.sem2.counter += 1;
    if(csem.sem1.waiting>0) { 
        csem.sem1.v();
        csem.p(); 
    }
    if(csem.sem2.waiting>0) { 
        csem.sem2.v(); 
        csem.p(); 
    }
    csem.v();
}


void* funkcja1(void* arg) {

    for(int i=0; i<10; i++)
    {
        P(firstSemaphore);
        P(secondSemaphore);
        P(secondSemaphore);
        std::cout << "Watek 1 w sekcji krytycznej A:" << firstSemaphore.counter << " B: " << secondSemaphore.counter << std::endl;
        V1V2();
    }

    return nullptr;
}

void* funkcja2(void* arg) {

    for(int i=0; i<10; i++)
    {
        P(firstSemaphore);
        P(secondSemaphore);
        P(secondSemaphore);
        std::cout << "Watek 2 w sekcji krytycznej A:" << firstSemaphore.counter << " B: " << secondSemaphore.counter << std::endl;
        V1V2();
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

// class MySemaphore
// {
//     pthread_mutex_t bin_semafor;
//     unsigned counter;

// public:
//     std::shared_ptr<MySemaphore> other;
//     MySemaphore(unsigned _counter): bin_semafor(PTHREAD_MUTEX_INITIALIZER), counter(_counter) {}

//     void P() {
//         if(counter>1) {
//             counter--;
//         }
//         else {
//             pthread_mutex_lock(&bin_semafor);
//             counter--;
//         }
//     }

//     void V1V2() {
//         if(counter == 0) {
//             pthread_mutex_unlock(&bin_semafor);
//             counter++;
//         }
//         else{
//             counter++;
//         }
//         if(other->counter == 0) {
//             pthread_mutex_unlock(&other->bin_semafor);
//             other->counter += 2;
//         }
//         else{
//             other->counter += 2;
//         }
//     }

//     void V2V1() {
//         if(counter == 0) {
//             pthread_mutex_unlock(&bin_semafor);
//             counter += 2;
//         }
//         else{
//             counter += 2;
//         }
//         if(other->counter == 0) {
//             pthread_mutex_unlock(&other->bin_semafor);
//             other->counter += 1;
//         }
//         else{
//             other->counter += 1;
//         }
//     }

//     void printCounter() {
//         std::cout << counter << std::endl;
//     }

// };

// auto first_ptr = std::make_shared<MySemaphore>(1);
// auto second_ptr = std::make_shared<MySemaphore>(1);




// void* funkcja1(void* arg) {

//     for(int i=0; i<10; i++)
//     {
//         first_ptr->P();
//         std::cout << "Watek 1 w sekcji krytycznej ";
//         first_ptr->printCounter();
//         first_ptr->V2V1();
//     }

//     return nullptr;
// }

// void* funkcja2(void* arg) {

//     for(int i=0; i<10; i++)
//     {
//         first_ptr->P();
//         std::cout << "Watek 2 w sekcji krytycznej ";
//         first_ptr->printCounter();
//         //first_ptr->V1V2();
//     }

//     return nullptr;
// }

// int main() {
//     pthread_t watek1, watek2;
//     // MySemaphore first(1);
//     // MySemaphore second(1);
//     first_ptr->other = second_ptr;
//     second_ptr->other = first_ptr;

//     pthread_create(&watek1, nullptr, funkcja1, nullptr);
//     pthread_create(&watek2, nullptr, funkcja2, nullptr);

//     pthread_join(watek1, nullptr);
//     pthread_join(watek2, nullptr);

//     return 0;
// }
#include "monitor.h"

class GeneralSemaphore
{
    Semaphore mutex;
    Semaphore sem1;
    Semaphore sem2;
    unsigned waiting1;
    unsigned waiting2;
    unsigned counter;

public:
    GeneralSemaphore(unsigned c) : counter(c), mutex(1), sem1(0), sem2(0), waiting1(0), waiting2(0) {}

    void P1()
    {
        mutex.p();
        if(counter == 0 || (counter == 1 && waiting2))
        {
            waiting1++;
            mutex.v();
            sem1.p();
            waiting1--;
        }
        counter--;
        mutex.v();
    }

    void P2()
    {
        mutex.p();


        mutex.v();
    }

    void V1()
    {
        mutex.p();


        mutex.v();
    }

    void V3()
    {
        mutex.p();


        mutex.v();
    }
};
#include "monitor.h"
#include <vector>

constexpr unsigned BUFF_SIZE = 10;

class Buffer
{
    Semaphore mutex;
    Semaphore semA;
    Semaphore semB;
    Semaphore full;
    Semaphore empty;
    bool readA = false;
    bool readB = false;
    // std::vector<int> values;
    int tab[BUFF_SIZE];
    unsigned free = 0;
    unsigned taken = 0;
    unsigned counter = 0;

    Buffer(): mutex(1), semA(1), semB(1), full(BUFF_SIZE), empty(0) {}

    void put(int value)
    {
        full.p();
        mutex.p();
        // values.push_back(value);
        //if(values.size() > 3)
          //  empty.v();
        tab[free] = value;
        free = (free+1)%BUFF_SIZE;
        counter++;
        if(counter > 3)
            empty.v();
        mutex.v();
    }

    int getA()
    {
        semA.p();
        empty.p();
        mutex.p();
        readA = true;
        // int value = values.front();
        int value = tab[taken];
        taken = (taken + 1) % BUFF_SIZE;
        counter--;
        if(readB)
        {
            // values.erase(values.begin());

            readA = readB = false;
            full.v();
        }
        else
        {
            empty.v();
        }
        semB.v();
        mutex.v();
        return value;
    }

    int getB()
    {
        semB.p();
        empty.p();
        mutex.p();
        readB = true;
        // int value = values.front();
        int value = tab[taken];
        taken = (taken + 1) % BUFF_SIZE;
        counter--;
        if(readA)
        {
            // values.erase(values.begin());

            readA = readB = false;
            full.v();
        }
        else
        {
            empty.v();
        }
        semA.v();
        mutex.v();
        return value;
    }
};
#include "monitor.h"
#include <vector>

constexpr unsigned BUFF_SIZE = 10;

class Buffer
{
    Semaphore mutex;
    Semaphore semA;
    Semaphore semB;
    Semaphore full;
    bool readA = false;
    bool readB = false;
    bool waitingA = true;
    bool waitingB = true;

    std::vector<int> values;

public:
    Buffer(): mutex(1), semA(0), semB(0), full(BUFF_SIZE) {}

    void put(int item)
    {
        full.p();
        mutex.p();
        values.push_back(item);
        if(waitingA && !readA)
        {
            semA.v();
            mutex.p();
        }
        else if(waitingB && !readB)
        {
            semB.v();
            mutex.p();
        }
        mutex.v();
    }

    void getA()
    {
        mutex.p();
        if(values.empty() || readA)
        {
            waitingA = true;
            mutex.v();
            semA.p();
            waitingA = false;
        }

        int value = values.front();
        readA = true;
        
        if(readB)
        {
            values.erase(values.begin());
            readA = readB = false;
            full.v();
            if(values.size() > 0 && !readB && waitingB)
            {
                semB.v();
                mutex.p();
            }
        }
        else if(values.size() > 0 && waitingB)
        {
            semB.v();
            mutex.p();
        }
        mutex.v();
    }

    void getB()
    {
        mutex.p();
        if(values.empty() || readB)
        {
            waitingB = true;
            mutex.v();
            semB.p();
            waitingB = false;
        }
        int value = values.front();
        readB = true;
        
        if(readA)
        {
            values.erase(values.begin());
            readA = readB = false;
            full.v();
        }
        if(waitingA && values.size()>0 && !readA)
        {
            semA.v();
            mutex.p();
        }

        mutex.v();
    }



};
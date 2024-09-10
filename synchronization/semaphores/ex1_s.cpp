#include <iostream>
#include "monitor.h"

class CoupledSemaphore
{
private:
    Semaphore mutex;
    Semaphore sem[2];
    unsigned counter[2];
    unsigned waiting[2];

public:
    CoupledSemaphore(unsigned _counter1, unsigned _counter2): counter{_counter1, _counter2}, sem{Semaphore(0), Semaphore(0)}, mutex(1), waiting{0, 0} {}

    void P(unsigned semNum) {
        mutex.p();
        if(counter[semNum] == 0) {
            waiting[semNum]++;
            mutex.v();
            sem[semNum].p();
            waiting[semNum]--;
        }
        counter[semNum]--;
        mutex.v();
    }

    void V1V2() {
        mutex.p();
        counter[0]++;
        counter[1] += 2;
        if(waiting[0] > 0) {
            sem[0].v();
            mutex.p();
        }
        if(waiting[1] > 0) {
            sem[1].v();
            mutex.p();
        }
        mutex.v();
    }

    void V2V1() {
        mutex.p();
        counter[1]++;
        counter[0] += 2;
        if(waiting[1] > 0) {
            sem[1].v();
            mutex.p();
        }
        if(waiting[0] > 0) {
            sem[0].v();
            mutex.p();
        }
        mutex.v();
    }
};

int main() {}
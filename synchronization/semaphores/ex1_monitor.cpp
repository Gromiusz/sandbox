#include <iostream>
#include "monitor.h"

class CoupledSemaphore
{
private:
    Monitor mon;
    Condition con[2];
    unsigned counter[2];

public:
    CoupledSemaphore(unsigned _counter1, unsigned _counter2): counter{_counter1, _counter2} {}

    void P(unsigned semNum) {
        mon.enter();
        if(counter[semNum] == 0) {
            mon.wait(con[semNum]);
        }
        counter[semNum]--;
        mon.leave();
    }

    void V1V2() {
        mon.enter();
        counter[0]++;
        counter[1] += 2;
        if(!con[1].empty()) {
            mon.signal(con[1]);
        }
        if(!con[0].empty()) {
            mon.signal(con[0]);
        }
        mon.leave();
    }

    void V2V1() {
        mon.enter();
        counter[1]++;
        counter[0] += 2;
        if(!con[0].empty()) {
            mon.signal(con[0]);
        }
        if(!con[1].empty()) {
            mon.signal(con[1]);
        }
        mon.leave();
    }
};

int main() {}
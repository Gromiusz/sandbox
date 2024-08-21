#include <queue>
#include <memory>
#include <thread>
#include <mutex>

#include <iostream>

using namespace std;

class Data {}; //nie zamieszczono skladowych

using PData = shared_ptr<Data>;

struct Queue {
    Queue() {}

    bool empty() {
        lock_guard<mutex> guard(m_);
        return q_.empty();
    }

    void push(PData data) {
        lock_guard<mutex> guard(m_);
        q_.push(data);
    }

    PData pop() {
        PData out;
        lock_guard<mutex> guard(m_);
        if(!q_.empty()) {
            out = q_.front();
            q_.pop();
        }
        return out;
    }

    mutex m_;
    std::queue<PData> q_;
};

void calculate(const Data& d) { //dlugotrwale obliczenia
    cout << "calculations begin" << endl;
    this_thread::sleep_for( chrono::milliseconds(1000) );
    cout << "calculations end" << endl;
}

void calc_thrd(Queue& q) {
    while(!q.empty()) {
        calculate(*q.pop());
    }
}

int main() {
     Queue q;
     //pominiÄto wÄtek do wstawiania obiektĂłw PData do kolejki q
     q.push(PData(new Data()));
     q.push(PData(new Data()));
     q.push(PData(new Data()));
     q.push(PData(new Data()));
     q.push(PData(new Data()));

     //tutaj wÄtki, ktĂłre pobierajÄ i przetwarzajÄ obiekty PData z kolejki
     thread thrd1( calc_thrd, ref(q) );
     thread thrd2( calc_thrd, ref(q) );
     thread thrd3( calc_thrd, ref(q) );
     thread thrd4( calc_thrd, ref(q) );
     thread thrd5( calc_thrd, ref(q) );

     thrd1.join();
     thrd2.join();
     thrd3.join();
     thrd4.join();
     thrd5.join();
}
//W aplikacji wystÄpuje blokada. WskaĹź przyczynÄ niepoprawnego dziaĹania i popraw bĹÄdny kod. Nie modyfikuj funkcji 'main'.

#include <list>
#include <thread>
#include <mutex>

#include <iostream>

using namespace std;

static const int NUM = 100;

/** klasa wejscia - wyjscia do kolejki znakow */
struct Queue {
    list<int> dane_;
    mutex mutex_;
};

struct Producent {

    Producent(Queue& in, Queue& out) : in_(in), out_(out) {}

    void operator()() {
        for(int num = 0; num < NUM; ) {
            //lock_guard<mutex> lock_in(in_.mutex_);
            //lock_guard<mutex> lock_out(out_.mutex_);
            if(!in_.dane_.empty() ) {
                int x;
                {
                    lock_guard<mutex> lock_in(in_.mutex_);
                    x = in_.dane_.front();
                    in_.dane_.pop_front();
                }
                
                
                cout << '.' << flush; //symuluje przetwarzanie danych
                lock_guard<mutex> lock_out(out_.mutex_);
                out_.dane_.push_back(x+1);
                ++num;
                
            }
        }
    }
    Queue& in_;
    Queue& out_;
};

struct Producent2 {

    Producent2(Queue& in, Queue& out) : in_(in), out_(out) {}

    void operator()() {
        for(int num = 0; num < NUM; ) {
            int x = 0; //data
            bool read = false;
            {
                lock_guard<mutex> lock_in(in_.mutex_);
                if(!in_.dane_.empty() ) {
                    read = true;
                    x = in_.dane_.front();
                    in_.dane_.pop_front();
                }
            }
            if(read) {
                cout << '.' << flush; //symuluje przetwarzanie danych
                ++num;

                lock_guard<mutex> lock_out(out_.mutex_);
                out_.dane_.push_back(x+1);
            }
        }
    }
    Queue& in_;
    Queue& out_;
};

int main() {
    Queue q1, q2;
    q1.dane_.push_back(1);
    Producent p1(q1, q2);
    Producent p2(q2, q1);

    thread thrd1( ref(p1) );
    thread thrd2( ref(p2) );
    thrd1.join();
    thrd2.join();
    return 0;
}
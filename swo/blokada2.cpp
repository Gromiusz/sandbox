#include <list>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>

#include <iostream>

using namespace std;

const int NUM = 100;

class Calc {
public:
    Calc(int idx) : idx_(idx) {
        out_.push_back(0);
        out_.push_back(0);
    }
    void setPrev(Calc* p) { prev_ = p; }

    int get() {
        int ret = -1;
        lock_guard<mutex> lock(m_);
         if(!out_.empty() ) {
             ret = out_.front();
             out_.pop_front();
         }
         return ret;
    }
    void operator()() {
        for(int i=0;i<NUM;++i) {
            
             if(prev_) {
                int x = prev_->get();
                std::this_thread::sleep_for( chrono::milliseconds(100)); //symuluje dĹugotrwaĹe lokalne obliczenia
                
                if( x >= 0) {
                    lock_guard<mutex> lock(m_);
                    out_.push_back(x + 1);
                }
            }
        }
    }
private:
    int idx_;
    Calc* prev_ = nullptr;
    list<int> out_;
    mutex m_;
};

int main () {
    Calc p1(1), p2(2), p3(3);
    p1.setPrev(&p3);
    p2.setPrev(&p1);
    p3.setPrev(&p2);

    thread thrd1( ref(p1) );
    thread thrd2( ref(p2) );
    thread thrd3( ref(p3) );
    thrd1.join();
    thrd2.join();
    thrd3.join();

    cout << "thrd1: " << p1.get() << endl;
    cout << "thrd2: " << p2.get() << endl;
    cout << "thrd3: " << p3.get() << endl;

    return 0;
}

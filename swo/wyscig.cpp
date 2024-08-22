// W aplikacji wystÄpuje wyĹcig. ProszÄ go wyeliminowaÄ dbajÄc o to, aby rozwiÄzanie byĹo skalowalne. Nie modyfikuj funkcji main. Aplikacja znajduje liczby pierwsze w kolekcji dostarczonych liczb.

// W funkcji main wystÄpujÄ obiekty ref(x). SÄ to obiekty pomocnicze, ktĂłre zapobiegajÄ tworzeniu kopii obiektu, wiÄc np. thread thrd1( ref(p1) ); oznacza, Ĺźe konstruktor std::thread nie wykona kopii obiektu p1. Nie jest to kluczowe do znalezienia rozwiÄzania.

// PosĹugujemy siÄ takĹźe wektorem liczb z biblioteki standardowej, oraz iteratorem. Iterator pokazuje na element w kolekcji (element w wektorze)

#include <vector>
#include <thread>
#include <mutex>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

const int N = 10000;

class InputNumbers  {
public:
    InputNumbers(const vector<long>& n) : numbers(n), current(numbers.begin()) {}

    long getNext() {
        lock_guard<mutex> lock(_mutex);
        if( current < numbers.end() ) {
            return *(current++);
        }
        else {
            return 0;
        }
    }
private:
    vector<long> numbers;
    vector<long>::const_iterator current;
    mutex _mutex;
};

class OutputNumbers {
public:
    OutputNumbers() {}

    void add(long n) {
        lock_guard<mutex> lock(_mutex);
        numbers.push_back(n);
    }

    vector<long>& get() { return numbers; }
private:
    vector<long> numbers;
    mutex _mutex;
};

//bada, czy n jest liczba pierwsza
bool isPrime(long n) {
    if( n <= 3) return true;
    if( n % 2 == 0) return false;
    for(long i = 3; i * i <= n; i = i + 2)
        if(n % i == 0) return false;
    return true;
}

class ThreadPrime {
public:
    ThreadPrime(InputNumbers& in, OutputNumbers& out) : input(in), output(out) { }

    //bada kolejne liczby z kolekcji input i dodaje liczbe do output, jezeli jest pierwsza
    void operator()() {

        for(long n = input.getNext(); n > 0; n = input.getNext() ) {
            if(isPrime(n) ) {
                output.add(n);
            }
        }
    }
private:
    InputNumbers& input;
    OutputNumbers& output;
};

int main () {
    vector<long> v(N); //wektor N liczb
    std::mt19937_64 gen; //generator losowy (Mersanne Twister, default seed)
    std::uniform_int_distribution<long> distr(1'000'000'000, 9'000'000'000);
    generate( v.begin(), v.end(), [&](){ return distr(gen);}); //N liczb losowych od 1*10^12 do 9*10^12

    InputNumbers input(v);
    OutputNumbers output;

    ThreadPrime t1(input, output);
    ThreadPrime t2(input, output);

    thread thrd1( ref(t1) );
    thread thrd2( ref(t2) );

    thrd1.join();
    thrd2.join();

    cout << "num primes:" << output.get().size() << endl;
    copy( output.get().begin(), output.get().end(), ostream_iterator<long>(cout, " ") ); //drukuje liczby pierwsze
    cout << endl;

    return 0;
}
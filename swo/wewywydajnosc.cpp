// KaĹźdy z obiektĂłw Data w kolekcji Out jest tworzony wykorzystujÄc stan systemu podczas obsĹugi zdarzenia zegara. Kolekcja Out nie jest uĹźywana zanim nie zostanie uzupeĹniona. Dostarczone rozwiÄzanie jest maĹo wydajne. SprĂłbuj poprawiÄ kod funkcji serve_event. W zadaniu wykorzystujemy funkcje anonimowe w C++, zwane takĹźe funkcjami lambda. Kod [&](const boost::system::error_code& error){ serve_event(out, t, error); } tworzy 1 argumentowÄ funkcjÄ anonimowÄ, argument jest typu const boost::system::error_code&, woĹanie tej funkcji sprawi, Ĺźe zostanie wywoĹana funkcja serve_event z argumentami out, t i error.

#include <vector>

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class Data {}; //nie zamieszczono skladowych

using PData = shared_ptr<Data>;

struct Out {
    Out(int size) : size_(size) {}

    int size_;
    std::vector<PData> v_;
    mutex m_;
};

void serve_event( Out& out, boost::asio::deadline_timer& t, const boost::system::error_code& error) {

    if( error ) return;

    // lock_guard<mutex> guard(out.m_);

    PData data = PData(new Data()); //tworzenie paczki danych, nie ma duĹźych kosztĂłw obliczeniowych, tego nie poprawiamy

    out.v_.push_back(data);

    if(out.v_.size() < out.size_) {
        t.async_wait([&](const boost::system::error_code& error){ serve_event(out, t, error); });
    }
}


int main() {

    Out out(500);

    boost::asio::io_service io;

    boost::asio::deadline_timer t1(io, boost::posix_time::milliseconds(8) );
    boost::asio::deadline_timer t2(io, boost::posix_time::milliseconds(13) );
    boost::asio::deadline_timer t3(io, boost::posix_time::milliseconds(21) );
    boost::asio::deadline_timer t4(io, boost::posix_time::milliseconds(34) );
    boost::asio::deadline_timer t5(io, boost::posix_time::milliseconds(55) );

    t1.async_wait([&](const boost::system::error_code& error){ serve_event(out, t1, error);});
    t2.async_wait([&](const boost::system::error_code& error){ serve_event(out, t2, error);});
    t3.async_wait([&](const boost::system::error_code& error){ serve_event(out, t3, error);});
    t4.async_wait([&](const boost::system::error_code& error){ serve_event(out, t4, error);});
    t5.async_wait([&](const boost::system::error_code& error){ serve_event(out, t5, error);});

    io.run();
    return 0;
}
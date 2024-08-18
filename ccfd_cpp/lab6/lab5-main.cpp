#include "lab5-lib.hpp"
#include <vector>
#include <list>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>

template <typename T>
struct LowFunctor
{
    bool operator()(const T& first, const T& second)
    {
        return first >= second;
    }
};

struct FunctorForSixExercise
{
    bool operator()(const int first)
    {
        return first >= limiter;
    }

    int limiter;
};

int global_limiter;

int main() {
    constexpr auto print_vector = [](const auto& vec) {
        for (const auto& el : vec) std::cout << el << ' ';
        std::cout << '\n';
    };

    { //////// 1 2
        auto vector = makeRandomVector<int>(12, 0, 10);
        // print_vector(makeRandomVector<int>(12, -2, 2));
        // //print_vector(makeRandomVector<char>(12, 65, 90));  
        // print_vector(makeRandomVector<double>(10, 0., 1.));
        print_vector(vector);
        std::sort(vector.begin(), vector.end());
        print_vector(vector);
        auto seven_count = std::count(vector.begin(), vector.end(), 7);
        std::cout << seven_count << std::endl;
    }
        
    {   //////////// 3
        auto vector3 = makeRandomVector<int>(12, 0, 20);
        auto vector33 = vector3;
        print_vector(vector3);
        print_vector(vector33);
        std::sort(vector3.begin(), vector3.end(), LowFunctor<int>());
        std::sort(vector33.begin(), vector33.end(), [](const int first, const int second){return first>second;});
        print_vector(vector3);
        print_vector(vector33);
    }
    
    {   /////////// 4
        auto vector = makeRandomVector<int>(20, 0, 10);
        print_vector(vector);
        auto counter = std::count_if(vector.begin(), vector.end(), [](const int number){return number > 7;});
        std::cout << counter << std::endl;
    }

    // {   ////// 5
    //     std::cin >> global_limiter;
    //     auto vector = makeRandomVector<int>(20, 0, 10);
    //     print_vector(vector);
    //     auto counter = std::count_if(vector.begin(), vector.end(), [](const int number){return number > global_limiter;});
    //     std::cout << counter << std::endl;
    // }

    // {   ////// 6
    //     FunctorForSixExercise functor;
    //     std::cin >> functor.limiter;
    //     auto vector = makeRandomVector<int>(20, 0, 10);
    //     print_vector(vector);
    //     auto counter = std::count_if(vector.begin(), vector.end(), functor);
    //     std::cout << counter << std::endl;
    // }

    // {   ////// 7
    //     int limiter;
    //     std::cin >> limiter;
    //     auto vector = makeRandomVector<int>(20, 0, 10);
    //     print_vector(vector);
    //     auto counter = std::count_if(vector.begin(), vector.end(), [&](const int num){return num > limiter;});
    //     std::cout << counter << std::endl;
    // }

    // { //// Cw 1
    //     std::string string;
    //     std::cin >> string;

    //     std::cout << (std::adjacent_find(string.begin(), string.end()) != string.end() ? 1 : 0) << std::endl;
    // }

    // { //// Cw 3
    //     std::string piesek = "piesek";
    //     std::string kotek = "kotek";

    //     std::string string;
    //     std::cin >> string;

    //     int pr = std::search(string.begin(), string.end(), piesek.begin(), piesek.end()) != string.end() ? 1 : 0;
    //     int kr = std::search(string.begin(), string.end(), piesek.begin(), kotek.end()) != kotek.end() ? 1 : 0;

    //     std::cout << (pr || kr) << std::endl;
    // }

    { //// Cw 5
        auto vector = makeRandomVector<int>(20, 0, 10);
        print_vector(vector);

        auto it = std::find(vector.begin(), vector.end(), 7);
        std::sort(vector.begin(), it);

        print_vector(vector);
    }

    { //// Cw 6
        auto vector = makeRandomVector<int>(30, 0, 10);
        print_vector(vector);

        vector.erase(std::remove(vector.begin(), vector.end(), 3), vector.end());
        print_vector(vector);

    }

    { //// Cw 7
        auto vector = makeRandomVector<int>(30, 0, 10);
        print_vector(vector);

        std::rotate(vector.begin(), std::find(vector.begin(), vector.end(), 7), vector.end());
        print_vector(vector);

    }

    { //// Cw 8
        auto vector = makeRandomVector<double>(10, -1, 1);
        print_vector(vector);

        std::cout << std::any_of(vector.begin(), vector.end(), [](const double num){return num > 0.9;}) << std::endl;
    }

    { //// Cw 9
        auto vector = makeRandomVector<double>(10, -1, 1);
        print_vector(vector);

        std::vector<double> out;
        std::transform(vector.begin(), vector.end(), std::back_inserter(out), [](const double num){return std::sin(num);});

        print_vector(vector);
        print_vector(out);
    }

    { //// Cw 10
        auto vector = makeRandomVector<int>(10, 0, 10);
        print_vector(vector);

        auto new_end = std::partition(vector.begin(), vector.end(), [](const int num){return num > 6;});
        std::sort(new_end, vector.end());

        print_vector(vector);
    }

    { //// Cw 11
        std::vector<unsigned> v = makeRandomVector<unsigned>(10, 0, 10);
        auto r = sorted_indices(v.begin(), v.end(), std::less<unsigned>{});
        int a = 0;
        for(size_t i = 0; i < v.size(); ++i)
        {
            assert(a <= v[r[i]]);
            a = v[r[i]];
        }

        print_vector(v);
        print_vector(r);
    }

}
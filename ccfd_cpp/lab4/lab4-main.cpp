#include "lab4-lib.hpp"
#include <iostream>

int main()
{
    int a = 5;
    int c = 2;
    Pair<int> pair;
    pair.first = 6;
    pair.second = 3;
    PairTable<int, 5> table;
    Pair<int> pair2{3, 4};
    Pair<int> pair3{1, 2};

    table[0] = pair;
    table[1] = pair2;
    table[2] = pair3;

    for(int i = 0; i < 3; i++)
    {
        std::cout << table[i].suma() << std::endl;
    }

    S<int> sint;
    S<double> sdouble;

    sint.print();
    sdouble.print();

    double tab[] = {3.2, 5.4, 3.1};
    std::cout << multiplyTab(tab, 3) << std::endl;
    std::cout << pairSum<int>(pair) << std::endl;
}
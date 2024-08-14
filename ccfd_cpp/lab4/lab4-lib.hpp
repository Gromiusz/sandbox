#pragma once

template<typename T>
class Pair
{
public:
    T first;
    T second;

    T suma();
};

// template<typename T, unsigned int N>
// class PairTable
// {

// }


template<typename T>
T Pair<T>::suma()
{
    return first + second;
}
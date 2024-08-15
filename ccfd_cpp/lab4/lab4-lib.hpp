#pragma once
#include <cstdio>

template<typename T>
class Pair
{
public:
    Pair(T _f, T _s): first(_f), second(_s) {}
    Pair() = default; 
    T first;
    T second;

    T suma();
};

template<typename T, unsigned int N>
class PairTable
{
public:
    Pair<T> table[N];

    Pair<T>& operator[](unsigned int num)
    {
        return table[num];
    }
};

template<typename T>
class PairTable<T, 0>
{};

template<typename T>
T Pair<T>::suma()
{
    return first + second;
}

template <typename T>
struct S 
{
    void print() { puts("Szablon ogólny"); }
};

template <>
struct S<double> 
{
    void print() { puts("Specjalizacja dla double"); }
};

template<typename T>
T multiplyTab(const T* tab, const size_t& size)
{
    T result = 1;
    for(int i=0; i<size; i++)
    {
        result *= tab[i];
    }
    return result;
}

template<typename T>
T pairSum(Pair<T>& pair)
{
    return pair.suma();
}
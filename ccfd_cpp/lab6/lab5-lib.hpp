#pragma once

#include <iostream>
#include <string>

#include <algorithm>
#include <concepts>
#include <random>
#include <vector>

/////////////////////////////////////////////////////
// Przeklej kawalek kodu ponizej. Wymagany C++20!
namespace detail {
template <typename T>
requires std::floating_point<T> || std::integral<T>
struct rand_dist {};

template <std::integral T>
struct rand_dist<T> {
    using type = std::uniform_int_distribution<T>;
};

template <std::floating_point T>
struct rand_dist<T> {
    using type = std::uniform_real_distribution<T>;
};
}  // namespace detail

template <typename T>
requires std::floating_point<T> || std::integral<T>
using rand_dist_t = detail::rand_dist<T>::type;

//
template <typename T>
requires std::floating_point<T> || std::integral<T>
auto makeRandomVector(std::size_t size, T min, T max) {
    static std::mt19937 prng{std::random_device{}()};
    rand_dist_t<T> random_dist{min, max};

    std::vector<T> result;
    result.reserve(size);
    std::generate_n(std::back_inserter(result), size,
                    [&] { return random_dist(prng); });
    return result;
}
//////////////////////////////////////////////////////

template < typename ConstIt, typename Comp >
std::vector< size_t > sorted_indices(ConstIt first, ConstIt last, Comp compare)
{
    std::vector<std::pair<int, size_t>> vec;
    for(int i = 0; i < std::distance(first, last); i++)
    {
        vec.push_back({*(first+i), i});
    }
    std::sort(vec.begin(), vec.end(), [&](std::pair<int, size_t> first, std::pair<int, size_t> second) { return compare(first.first, second.first); });

    std::vector<size_t> out;
    for(int i=0; i<vec.size(); i++)
    {
        out.push_back(vec[i].second);
    }

    return out;
}

// template <typename ConstIt, typename Comp>
// std::vector<size_t> sorted_indices(ConstIt first, ConstIt last, Comp compare) {
//     std::vector<size_t> v(std::distance(first, last));
//     std::iota(begin(v), end(v), 0u);

//     std::sort(begin(v), end(v),
//               [&](size_t a, size_t b) { return compare(first[a], first[b]); });

//     return v;
// }
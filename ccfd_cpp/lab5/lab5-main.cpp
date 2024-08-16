#include "lab5-lib.hpp"
#include <vector>
#include <list>

int main()
{
    std::vector<int> vec{100,42};
    std::vector<int> vec2(100,42);

    std::cout << vec.size() << std::endl;
    std::cout << vec.capacity() << std::endl << std::endl;

    for(const auto& el : vec)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;

    // for(int i=0; i<100; i++)
    // {
    //     vec.push_back(i);
    //     std::cout << &vec[i] << std::endl;
    //     std::cout << vec.size() << std::endl;
    //     std::cout << vec.capacity() << std::endl << std::endl;
    // }

    std::vector<Human> strvec;

    // while(true)
    // {
    //     std::string word;
    //     std::cin >> word;
    //     if(word == "pop")
    //     {
    //         strvec.pop_back();
    //     }
    //     else{
    //         strvec.emplace_back(std::move(word));
    //     }
        

    //     for(const auto& el: strvec)
    //     {
    //         std::cout << el.name << " ";
    //     }
    //     std::cout << std::endl;
    // }


    std::list<int> list;
    list.push_back(34);
    auto it = list.crbegin();
    
    for(const auto& el: list)
    {
        std::cout << *it++ << " ";
    }
    std::cout << std::endl;
}
#include <iostream>
#include <map>
#include <memory>
#include "custom_allocator.h"
#include "custom_container.h"


struct hard {
    int fa = 0;
    int fi = 0;
    hard(int fa, int fi) : fa(fa), fi(fi) {};

    hard() = delete;
    hard(const hard &) = delete;
    hard(hard &&) noexcept = delete;

    ~hard() = default;
};

constexpr int factorial( int number )
{
    return (number == 0) ? 1 : number * factorial(number-1);
}

constexpr  int fibonacci( int number )
{
    return (number == 0 || number == 1) ? 1 : fibonacci(number-1) + fibonacci(number - 2);
}

int main()
{
    auto map = std::map<int, hard>{};

    for( auto i = 0; i < 10; i++ )
    {
        map.emplace(std::piecewise_construct,
                    std::forward_as_tuple(i),
                    std::forward_as_tuple(factorial(i), fibonacci(i)));
    }

    for(const auto& element : map)
    {
        std::cout << element.first << " " << element.second.fa << " " << element.second.fi << std::endl;
    }

    auto mapCustomAllocator = std::map<int, hard, std::less<int>, custom_allocator<std::pair<const int, hard>, 10>>{};

    for( auto i = 0; i < 10; i++ )
    {
        mapCustomAllocator.emplace(std::piecewise_construct,
                    std::forward_as_tuple(i),
                    std::forward_as_tuple(factorial(i), fibonacci(i)));
    }

    for(const auto& element : mapCustomAllocator)
    {
        std::cout << element.first << " " << element.second.fa << " " << element.second.fi << std::endl;
    }

    auto customContainer = custom_container<hard>{};

    for( auto i = 0; i < 10; i++ )
    {
        customContainer.emplace_back(factorial(i), fibonacci(i));
    }

    for(const auto& element : customContainer)
    {
        std::cout << element.fa << " " << element.fi << std::endl;
    }
//
//    auto customContainerAllocator = custom_container<hard, custom_allocator<hard, 10> >{};
//
//    for( auto i = 0; i < 10; i++ )
//    {
//        customContainerAllocator.emplace_back(factorial(i), fibonacci(i));
//    }
//
//    for(const auto& element : customContainerAllocator)
//    {
//        std::cout << element.fa << " " << element.fi << std::endl;
//    }

    return 0;
}
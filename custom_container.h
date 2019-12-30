#pragma once

#include <list>

template<typename T, class Allocator = std::allocator<T> >
class custom_container
{
public:
    using value_type = T;

    using Container = std::list<value_type, Allocator>;

public:
    custom_container() = default;
    ~custom_container() = default;

    template< typename... Args >
    void  emplace_back( Args &&...args )
    {
        m_Container.emplace_back(std::forward<Args>(args)...);
    }

    auto begin() const
    {
        return m_Container.begin();
    }

    auto end() const
    {
        return m_Container.end();
    }

private:
    Container m_Container;
};

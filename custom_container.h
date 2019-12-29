#pragma once

#include <map>

template<typename U, typename T, class Allocator = std::allocator<T> >
class custom_container
{
public:
    using key_type = U;
    using mapped_type = T;

    using Container = std::map<key_type, mapped_type, std::less<int>,Allocator>;

public:
    custom_container() = default;
    ~custom_container() = default;

    template< typename... Args >
    void  emplace( Args &&...args )
    {
        m_Container.emplace(std::forward<Args>(args)...);
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

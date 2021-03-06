#pragma once

#include <list>

template<typename T, int reserveCount>
class custom_allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

    template<typename U>
    struct rebind {
        using other = custom_allocator<U, reserveCount>;
    };

    pointer allocate(size_type n) {
        void* p = nullptr;

        if(m_Counter == 0)
        {
            p = std::malloc(reserveCount * sizeof(T));

            if (!p)
            {
                throw std::bad_alloc();
            }

            m_Pointers.push_back( reinterpret_cast<pointer>(p));
            ++m_Counter;
        }
        else
        {
            p = m_Pointers.back() + m_Counter;

            if(++m_Counter >= reserveCount)
            {
                m_Counter = 0;
            }
        }

        ++m_Number;

        return reinterpret_cast<T *>(p);
    };

    void deallocate(pointer p, size_type n) {
        if(--m_Number == 0)
        {
            for(const auto& element : m_Pointers)
            {
                std::free(element);
            }

            m_Pointers.clear();
        }
    };

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) const {
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) const {
        p->~T();
    }


private:
    using PointerList = std::list<pointer>;

    int m_Counter = 0;
    int m_Number = 0;
    PointerList m_Pointers;
};


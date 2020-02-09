#pragma once


template<typename T, class Allocator = std::allocator<T> >
class custom_container
{
public:
    using value_type = T;

private:
    struct Node;

    using node_type = Node;
    using node_pointer_type = std::shared_ptr<node_type>;

    struct Node
    {
        value_type m_Value{};
        node_pointer_type m_NextNode;

        template< typename... Args>
        Node( Args &&...args ) : m_Value(std::forward<Args>(args)...){}
        ~Node() = default;
    };

    class Iterator
    {
    private:
        using self_type = Iterator;
        using value_type = node_pointer_type;
        using pointer = value_type;
        using iterator_category = std::forward_iterator_tag;

    public:
        Iterator(pointer ptr) : m_Ptr(ptr) { }
        auto operator++() { auto i = *this; m_Ptr=m_Ptr->m_NextNode; return i; }
        auto operator++(int junk) { m_Ptr=m_Ptr->m_NextNode; return *this; }
        auto operator*() { return &m_Ptr->m_Value; }
        auto operator->() { return m_Ptr->m_Value; }
        bool operator==(const self_type& rhs) { return m_Ptr == rhs.m_Ptr; }
        bool operator!=(const self_type& rhs) { return m_Ptr != rhs.m_Ptr; }

    private:
        pointer m_Ptr;
    };

public:
    custom_container() = default;
    ~custom_container() = default;

    template< typename... Args >
    void  emplace_back( Args &&...args )
    {
        if(m_Root == nullptr)
        {
            m_Root = m_Last = std::make_shared<node_type>(std::forward<Args>(args)..., std::default_delete<value_type>(), Allocator());
        }
        else
        {
            auto nextNode = std::make_shared<node_type>(std::forward<Args>(args)..., std::default_delete<value_type>(), Allocator());
            m_Last->m_NextNode = nextNode;
            m_Last = nextNode;
        }
    }

    auto begin() const
    {
        return Iterator(m_Root);
    }

    auto end() const
    {
        return Iterator( nullptr);
    }

private:
    node_pointer_type m_Root;
    node_pointer_type m_Last;
};

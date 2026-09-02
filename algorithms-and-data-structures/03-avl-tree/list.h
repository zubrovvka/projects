#ifndef AVL_TREE_LIST_H
#define AVL_TREE_LIST_H

#include <cstdlib>
#include <iostream>

template <class T> class List
{
private:
    struct Node
    {
        T value;
        explicit Node(T val = T()) : value(val) {}
        Node* next = nullptr;
    };
    Node* head = nullptr;
    unsigned list_size = 0;

public:
    explicit List(unsigned size = 0, const T& val = T())
    {
        //         Constructor that can gets 'size' or/and 'val' values
        resize(size);
        if (val != T() && size != 0)
        {
            Node* ptr = head;
            for (unsigned i = 0; i < list_size; i++)
            {
                ptr->value = val;
                ptr = ptr->next;
            }
        }
    };
    List(const List<T>& copy)
    {
        // Copy constructor
        *this = copy;
    };
    ~List()
    {
        resize(0);
    };
    unsigned size() const;
    void resize(unsigned size);
    bool insert(unsigned pos, const T& val);
    void push_back(const T& val);
    bool contains(const T& val);
    int find(const T& val);
    T pop(int index);
    void clear();
    bool empty();
    T& operator[](int index);
    List<T>& operator=(List<T> const& obj);

    template <class X> friend std::ostream& operator<<(std::ostream& buff, List<X>& list);
};

#include "list.tpp"

#endif // AVL_TREE_LIST_H

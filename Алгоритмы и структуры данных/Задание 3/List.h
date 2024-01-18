#ifndef LAB1_LIST_H
#define LAB1_LIST_H

#include <cstdlib>
#include <iostream>

template <class T>
class List {
private:
    struct Node {
        T value;
        explicit Node(T val = T()): value(val) {}
        Node * next = nullptr;
    };
    Node * head = nullptr;
    unsigned list_size = 0;
public:
    explicit List(unsigned size = 0, const T &val = T()) {
//         Constructor that can gets 'size' or/and 'val' values
        resize(size);
        if (val != T() && size != 0){
            Node * ptr = head;
            for (int i = 0; i < list_size; i++){
                ptr->value = val;
                ptr = ptr->next;
            }
        }
    };
    List(List<T> &copy) {
        // If constructor gets List object doing copy
        head = new Node();
        Node * m = head;
        for (int i = 0; i < copy.list_size - 1; i++) {
            m->next = new Node;  // Creating new Node, if current size less than new
            m->value = copy[i];
            m = m->next;
        }
        m->value = copy[-1];
        list_size = copy.list_size;
    };
    ~List() {
        resize(0);
    };
    unsigned size() const;
    void resize(unsigned size);
    bool insert(unsigned pos, const T &val);
    void push_back(const T &val);
    bool contains(const T &val);
    int find(const T &val);
    T pop(int index);
    void clear();
    bool empty();
    T& operator [] (int index);
    List<T>& operator = (List<int> const &obj);

    template<class X>
    friend std::ostream& operator << (std::ostream &buff, List<X> &list);
};

#endif //LAB1_LIST_H
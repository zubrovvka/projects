#include "List.h"

template<class T>
void List<T>::resize(unsigned new_size) {
    if (list_size == 0 && new_size != 0)
        head = new Node;
    Node * m = head;
    if (new_size > list_size) {
        for (int i = 0; i < new_size - 1; i++) {
            if (list_size == 0 || (i >= list_size - 1)){
                m->next = new Node;  // Creating new Node, if current size less than new
            }
            m = m->next;
        }
    } else {
        // Deleting Nodes from "head", if new size less than current
        for (int i = 0; i < list_size - new_size; i++) {
            m = head->next;
            delete head;
            head = m;
        }
    }
    list_size = new_size;
}

template<class T>
unsigned List<T>::size() const {
    return list_size;
}

template<class T>
T& List<T>::operator [] (int index) {
    if (index < 0) // Feature to get value from end of list (with negative index)
        index = list_size + index;
    if (index >= list_size || index < 0)
        exit(1);
    Node * m = head;
    for (int i = 0; i < list_size; i++) {
        if (i == index)
            return m->value;
        else
            m = m->next;
    }
    return head->value;
}

template<class T>
List<T>& List<T>::operator = (List<int> const &obj) {
    if (head != obj.head) {
        resize(obj.list_size);  // Creating new
        Node * self = head;
        Node * other = obj.head;
        for (int i = 0; i < list_size; i++){
            self->value = other->value;
            self = self->next;
            other = other->next;
        }
    }
    return *this;
}

template<class T>
int List<T>::find(const T &val) {
    Node * m = head;
    int i = 0;
    while (m){
        if (m->value == val)
            return i;
        m = m->next;
        i++;
    }
    return -1;
}

template<class T>
bool List<T>::contains(const T &val) {
    if (find(val) == -1)
        return false;
    return true;
}

template<class T>
bool List<T>::insert(unsigned int pos, const T &val) {
    if (pos > list_size && pos != 0)
        return false;
    Node * m = head;
    if (pos > 0) {
        Node * g;
        for (int i = 0; i < list_size; i++) {
            if (pos == i + 1) {
                g = m->next;
                m->next = new Node;
                m->next->value = val;
                m->next->next = g;
                break;
            }
            m = m->next;
        }
    } else {
        m = new Node;
        m->value = val;
        m->next = head;
        head = m;
    }
    list_size++;
    return true;
}

template<class T>
void List<T>::push_back(const T &val) {
    insert(list_size, val);
}

template<class T>
T List<T>::pop(int index) {
    if (index < 0)
        index = list_size + index;
    if (index < 0)
        exit(1);
    T value;
    Node * temp = head;
    Node * toDel;
    if (index > 0){
        for (int i = 0; i < index - 1; i++)
            temp = temp->next;
        value = temp->next->value;
        toDel = temp->next;
        temp->next = temp->next->next;
    } else {
        value = head->value;
        toDel = head;
        head = head->next;
    }
    delete toDel;
    list_size--;
    return value;
}

template<class T>
void List<T>::clear() {
    resize(0);
}

template <class T>
std::ostream& operator << (std::ostream &buff, List<T> &list) {
    buff << '[';
    int size = list.size();
    for (int i = 0; i < size; i++) {
        buff << list[i];
        if (i != size - 1)
            buff << ", ";
    }
    buff << "]";
    return buff;
}

template<class T>
bool List<T>::empty() {
    return head == nullptr;
}

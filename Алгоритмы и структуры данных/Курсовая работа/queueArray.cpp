#include "queuearray.h";

QueueArray::QueueArray() {
    count = 0;
    data = NULL;
}

QueueArray::~QueueArray() {
    delete[] data;
}

bool QueueArray::empty() {
    return (count == 0);
}

int QueueArray::size() {
    return count;
}

int QueueArray::front() {

    if (count > 0)
        return (data[0]);
    else
        return -1;
}

void QueueArray::push(const int& val) {
    int* newData = new int[count + 1];

    for (int i = 0; i < count; i++) {
        newData[i] = data[i];
    }
    newData[count] = val;
    delete[] data;
    data = newData;
    count++;
}

void QueueArray::pop() {
    int* newData = new int[count - 1];
    if (count > 1) {
        for (int i = 0; i < count - 1; i++) {
            newData[i] = data[i + 1];
        }
    }
    delete[] data;
    data = newData;
    count--;
}
void QueueArray::print() {
    for (int i = 0; i < count; i++) {
        cout << data[i];
    }
    cout << endl;
}
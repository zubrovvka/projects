#include <iostream>
#include "DynArray.h"


DynArray::DynArray()
{
    count = 0;
    data = NULL;
}

DynArray::~DynArray()
{
    delete[] data;
}

void DynArray::add(const int s) {
    int* newData = new int[count + 1];
    for (int i = 0; i < count; i++) {
        newData[i] = data[i];
    }
    newData[count] = s;
    delete[] data;
    data = newData;
    count++;
}

void DynArray::set(const int index, const int s) {
    data[index] = s;
}

int DynArray::read(const int index) {
    return data[index];
}

int DynArray::size() {
    return count;
}

void DynArray::clear() {
    count = 0;
    delete[] data;
    data = NULL;
}

int DynArray::findset(int ind) // возвращает идентификатор множества, которому принадлежит элемент 
{
    if (ind == data[ind])
    {
        return ind;
    }
    else
    {
        return findset(data[ind]);
    }
}

void DynArray::unionset(int f, int t) // объединение двух множеств
{
    data[f] = data[t];
}
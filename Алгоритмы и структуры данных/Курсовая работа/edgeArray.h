#pragma once
#include <iostream>
#include "edge.h"

class edgeArray // ����� ������������ ����� ������ ��������� ���� edge
{
public:
    
    edgeArray() // ����������� ������ 
    {
        size = 0;
        arr = NULL;
    }
    ~edgeArray() {
        delete[] arr;
    }


    void add(edge v) // ���������� ������ �������� � ������
    {
        edge* newArr = new edge[size + 1];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        newArr[size] = v;
        delete[] arr;
        arr = newArr;
        size++;
    }

    edge get(int ind) // ������� ���������� ������� �� �������
    {
        return arr[ind];
    }

    int getf(int ind) // ������� ���������� ��������� ������� ����� �� �������
    {
        return arr[ind].from;
    }

    int gett(int ind)  // ������� ���������� �������� ������� ����� �� �������
    {
        return arr[ind].to;
    }

    int getw(int ind) // ������� ���������� ��� ����� �� �������
    {
        return arr[ind].weight;
    }

    void set(int ind, edge e)
    {
        arr[ind] = e;
    }

    int _size() {
        return size;
    }

    void clear() {
        delete[] arr;
        arr = NULL;
        size = 0;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i].from << " - " << arr[i].to << endl;
        }
    }

private:
    int size;
    edge* arr;
};


#pragma once
#include <iostream>
using namespace std;


class QueueArray {
public:
	QueueArray();
	~QueueArray();
	int   size();
	void  push(const int& val);
	void  pop();
	bool  empty();
	int   front();
	void  print();
private:
	int		count;
	int* data;
};
#pragma once
using namespace std;

class DynArray
{
public:
	DynArray();
	~DynArray();
	void add(const int s);
	int read(const int index);
	void set(const int index, const int s);
	int size();
	void clear();
	int findset(int ind);
	void unionset(int f, int t);
private:
	int count;
	int* data;
};
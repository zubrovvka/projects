#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "queuearray.h";

using namespace std;


// ���� ���-�� ������
const int TOP_COUNT_MAX = 50;
// ��������� ��������
const int EDGE_VAL_MIN = 0;
const int EDGE_VAL_MAX = 1023;

// �������� ����� ����������
class App {
public:
	App(const string path);
	~App();
	int run();
private:
	// ���������� ����� �����
	bool run_proc = true;
	// ���� � ����� ������� ���������
	string filepath;
	// ������ ������� (������������)
	int msize = 0;
	// ������ ������ (�����)
	string* vertices = NULL;
	// ������� ��������� msize * msize
	int** matrix = NULL;
	// ������ ��������� ��� ������
	int* visited = NULL;
	// �������� � �������� ������ 
	void initArrays();
	void addVertex(const string val);
	// �������� � �������� ���������
	void setMatrix(const int row, const int col, const int val);
	void initMatrix();
	void readMatrixFromFile();
	void printMatrix();
	// ���� ������������
	void showMenu();
	// ����� � ������� depth-first search
	void dfsAlg();
	void dfs(const int v);

	// ����� � ������ breadth-first search
	void bfsAlg();
	void bfs(const int v);
};


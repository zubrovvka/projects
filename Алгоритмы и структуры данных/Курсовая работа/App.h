#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "queuearray.h";

using namespace std;


// Макс кол-во вершин
const int TOP_COUNT_MAX = 50;
// Диапазоны значений
const int EDGE_VAL_MIN = 0;
const int EDGE_VAL_MAX = 1023;

// Основной класс приложения
class App {
public:
	App(const string path);
	~App();
	int run();
private:
	// Переменная цикла ввода
	bool run_proc = true;
	// Путь к файлу матрицы смежности
	string filepath;
	// Размер матрицы (симметричная)
	int msize = 0;
	// Массив вершин (имена)
	string* vertices = NULL;
	// Матрица смежности msize * msize
	int** matrix = NULL;
	// Массив посещений для обхода
	int* visited = NULL;
	// Операции с массивом вершин 
	void initArrays();
	void addVertex(const string val);
	// Операции с матрицей смежности
	void setMatrix(const int row, const int col, const int val);
	void initMatrix();
	void readMatrixFromFile();
	void printMatrix();
	// Меню пользователя
	void showMenu();
	// Обход в глубину depth-first search
	void dfsAlg();
	void dfs(const int v);

	// Обход в ширину breadth-first search
	void bfsAlg();
	void bfs(const int v);
};


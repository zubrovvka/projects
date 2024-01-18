
#include "App.h"

// Конструктор
App::App(const string path) {
	filepath = path;
}

// Деструктор
App::~App() {
}

// Меню пользователя
void App::showMenu() {
	cout << " Select Option number." << endl;
	cout << "0. Run Kruskal algorithm" << endl;
	cout << "1. Run depth-first search algorithm" << endl;
	cout << "2. Run breadth-first search algorithm" << endl;

	int option;

	cin >> option;
	switch (option) {
	case 0:
		run_proc = false;
		break;
	case 1:
		dfsAlg();
		break;
	case 2:
		bfsAlg();
		break;
	case 3:
		printMatrix();
		break;
	default:
		cout << "Unknown option" << endl;
		break;
	}
}

// Основной цикл приложения
int App::run() {

	while (run_proc) {
		readMatrixFromFile();
		showMenu();
		system("pause");
	}
	return 0;
}

// Создание массива для матрицы
void App::initMatrix() {
	matrix = new int* [msize];
	for (int i = 0; i < msize; i++) {
		matrix[i] = new int[msize];
	}
	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			matrix[i][j] = 0;
		}
	}
}

// Очистка массивов вершин и матрицы
void App::initArrays() {
	delete[] vertices;
	vertices = NULL;
	for (int i = 0; i < msize; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = NULL;
	msize = 0;
}

// Добавить вершину
void App::addVertex(const string val) {
	string* newVert = new string[msize + 1];
	for (int i = 0; i < msize; i++) {
		newVert[i] = vertices[i];
	}
	newVert[msize] = val;
	delete[] vertices;
	vertices = newVert;
}

// Заполнить значение в матрице
void App::setMatrix(const int row, const int col, const int val) {
	matrix[row][col] = val;
}

// Чтение матрицы из файла
void App::readMatrixFromFile() {
	ifstream f_in;
	string s, token;

	int i, j, len, val, row, col;
	bool err;

	// Инит массивов
	initArrays();
	// Считать строку с заголовками
	f_in.open(filepath);
	getline(f_in, s);
	len = s.length();

	//Обработать вершины
	err = false;
	i = 0;
	token = "";
	while (!err && i < len) {

		if ((s[i] >= 'A' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')) {
			// Новая вершина
			token += s[i];
		}
		else if (s[i] == ' ' || '\t') {
			if (token != "") {
				// Записать в массив вершин
				addVertex(token);
				msize++;
				token = "";

				if (msize > TOP_COUNT_MAX) {
					err = true;
					cout << "Wrong quantity of vertex" << endl;
				}
			}
		}
		else {
			err = true;
			cout << "Wrong symbols in header" << endl;
		}
		i++;
		if (i == len && token != "") {
			// Последняя вершина
			addVertex(token);
			msize++;
			token = "";

			if (msize > TOP_COUNT_MAX) {
				err = true;
				cout << "Wrong quantity of vertex" << endl;
			}
		}
	}

	// Обработка матрицы
	if (!err) {
		initMatrix();
	}
	i = 0;
	token = "";
	row = 0;
	col = 0;
	while (!err && getline(f_in, s)) {
		len = s.length();
		token = "";
		i = 0;
		val = 0;
		col = 0;
		if (row == msize) {
			err = false;
			cout << "Wrong quantity of rows in body" << endl;
		}
		while (!err && i < len) {
			if (col == msize) {
				err = true;
				cout << "Wrong quantity of cols in body" << endl;
			}
			if (s[i] >= '0' && s[i] <= '9') {
				// Новое значение
				token += s[i];
				val *= 10;
				val += s[i] - '0';
			}
			else if (s[i] == ' ' || '\t') {
				if (token != "") {
					// Записать значение
					if (val >= EDGE_VAL_MIN && val <= EDGE_VAL_MAX) {

						setMatrix(row, col, val);
						if ((row > col) && (matrix[row][col] != matrix[col][row])) {
							//err = true;
							//cout << "Value row: " << row << " col: " << col << " val: " << val << " isn't symmetrical" << endl;
						}
						token = "";
						col++;
						val = 0;
					}
					else {
						err = true;
						cout << "Wrong value row: " << row << " col: " << col << " val: " << val << endl;
					}
				}
			}
			else {
				err = true;
				cout << "Wrong symbols in body" << endl;
			}
			i++;
			if (i == len && token != "") {
				// последнее значение
				if (val >= EDGE_VAL_MIN && val <= EDGE_VAL_MAX) {
					setMatrix(row, col, val);
					if ((row > col) && (matrix[row][col] != matrix[col][row])) {
						//err = true;
						//cout << "Value row: " << row << " col: " << col << " val: " << val << " isn't symmetrical" << endl;
					}
					token = "";
					col++;
					val = 0;
				}
				else {
					err = true;
					cout << "Wrong value row: " << row << " col: " << col << " val: " << val << endl;
				}
			}
		}
		row++;
	};
	if (!err) {
		cout << "File " << filepath << " was read successfuly" << endl;
	}
	f_in.close();
}

void App::printMatrix() {

	if (vertices != NULL && matrix != NULL) {
		for (int i = 0; i < msize; i++) {
			/*if (vertices[i].length() > 1) {
				cout << vertices[i] << "  ";
			}
			else{
				cout << vertices[i] << " ";
			}*/
			cout << vertices[i] << '\t';
		}
		cout << endl;
		for (int i = 0; i < msize; i++) {
			for (int j = 0; j < msize; j++) {
				/*if (matrix[i][j] > 9) {
					cout << matrix[i][j] << "  ";
				}
				else {
					cout << matrix[i][j] << "   ";
				}*/
				cout << matrix[i][j] << '\t';
			}
			cout << endl;
		}
	}
};

// Обход в глубину depth-first search
void App::dfsAlg() {
	if (matrix != NULL) {
		visited = new int[msize + 1];
		// Обнуляем массив посещений
		for (int i = 0; i < msize; i++) {
			visited[i] = 0;
		}
		cout << "DFS Route is: ";
		dfs(0);
		cout << endl;
	}
}
void App::dfs(const int v) {
	// Посетили саму вершину
	visited[v] = 1;
	cout << vertices[v] << " ";
	for (int j = 0; j < msize; j++) {
		// Если есть наследник и он её не посещен
		if ((matrix[v][j] > 0) && (!visited[j])) {
			// посещаем наследника
			dfs(j);
		}
	}
}

// Обход в ширину breadth-first search
void App::bfsAlg() {
	if (matrix != NULL) {
		visited = new int[msize + 1];
		// Обнуляем массив посещений
		for (int i = 0; i < msize; i++) {
			visited[i] = 0;
		}
		cout << "BFS Route is: ";
		bfs(0);
		cout << endl;
	}
}
void App::bfs(const int v) {
	// Очередь пройденных вершин
	QueueArray* q = new QueueArray();
	// Индекс вершины
	int v_ind;
	// Посетили саму вершину
	q->push(v);
	cout << vertices[v] << " ";
	visited[v] = 1;
	// пока очеред не пуста
	while (!q->empty()) {
		// извлечь вершину из гловы очереди
		v_ind = q->front();
		q->pop();
		// всех связный первого уровня непосещенных посещаем и в очередь
		for (int j = 0; j < msize; j++) {
			if ((matrix[v_ind][j] > 0) && (!visited[j])) {
				visited[j] = 1;
				q->push(j);
				cout << vertices[j] << " ";
			}
		}
	}
}

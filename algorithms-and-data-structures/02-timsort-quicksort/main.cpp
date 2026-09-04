#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

using namespace std;

void printArr(const vector<int>& arr) // вывод массива
{
    cout << "Ваш массив: " << "\n";
    for (size_t i = 0; i < arr.size(); i++)
        cout << arr.at(i) << " ";
    cout << "\n";
}

void quickSort(vector<int>& arr, int left, int right) // быстрая сортировка (на месте)
{
    int i = left;
    int j = right;
    int tmp;
    int mid = arr[(left + right) / 2];
    while (i <= j)
    {
        while (arr[i] < mid)
            i++;
        while (arr[j] > mid)
            j--;
        if (i <= j)
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    // рекурсия
    if (left < j)
        quickSort(arr, left, j);
    if (right > i)
        quickSort(arr, i, right);
}

int getMinrun(int n) // определение минимального размера подмассива
{
    int r = 0;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void insertionSort(vector<int>& arr, int left, int right) // сортировка вставками
{
    for (int i = left + 1; i <= right; i++)
    {
        int tmp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp;
    }
}

void merge(vector<int>& arr, int left1, int mid, int right1) // сортировка слиянием
{
    int len1 = mid - left1 + 1;
    int len2 = right1 - mid;
    int* left = new int[len1];
    int* right = new int[len2];
    for (int i = 0; i < len1; i++)
        left[i] = arr[left1 + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[mid + 1 + i];
    int i = 0;
    int j = 0;
    int k = left1;
    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < len1)
    {
        arr[k] = left[i];
        k++;
        i++;
    }
    while (j < len2)
    {
        arr[k] = right[j];
        k++;
        j++;
    }
    delete[] left;
    delete[] right;
}

void timSort(vector<int>& arr, int n) // сортировка TimSort
{
    int minrun = getMinrun(n);
    for (int i = 0; i < n; i += minrun)
    {
        int min;
        if ((i + (minrun - 1)) >= (n - 1))
            min = n - 1;
        else
            min = i + (minrun - 1);
        insertionSort(arr, i, min);
    }
    for (int size = minrun; size < n; size = 2 * size)
    {
        for (int left = 0; left < n; left += 2 * size)
        {
            int min;
            if ((left + 2 * size - 1) >= (n - 1))
                min = n - 1;
            else
                min = left + 2 * size - 1;
            int mid = left + size - 1;
            int right = min;
            merge(arr, left, mid, right);
        }
    }
}

void chooseAndSort(vector<int>& arr) // Выбор алгоритма, сортировка и замер времени
{
    int variant;
    cout << "Выберите способ сортировки:" << "\n";
    cout << "1-timSort" << "\n";
    cout << "2-quickSort" << "\n";
    cin >> variant;
    if (variant != 1 && variant != 2)
    {
        cout << "Выберите значения 1 или 2" << "\n";
        return;
    }
    auto start = chrono::high_resolution_clock::now();
    if (variant == 1)
        timSort(arr, arr.size());
    else
        quickSort(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    printArr(arr);
    cout << "Время сортировки: " << duration.count() << " мс" << "\n";
}

void manualInput() // Ввод вручную массива
{
    int k;
    cout << "Введите колличество элементов в массиве: " << "\n";
    cin >> k;
    vector<int> arr(k);
    cout << "Введите значения элементов: " << "\n";
    for (int i = 0; i < k; i++)
    {
        cin >> arr[i];
    }
    printArr(arr);
    chooseAndSort(arr);
}

void randomInput() // Заполнение массива рандомными числами
{
    int k;
    cout << "Введите колличество элементов в массиве: " << "\n";
    cin >> k;
    vector<int> arr(k);
    for (int i = 0; i < k; i++)
        arr[i] = rand() % 100 - 15;
    printArr(arr);
    chooseAndSort(arr);
}

template <class V> class dynamic_array
{
private:
    int arraySize;

public:
    V* arrayData; // Создание пустого массива
    dynamic_array()
    {
        arraySize = 0;
        arrayData = NULL;
    }
    ~dynamic_array()
    {
        delete[] arrayData;
    }
    void push_back(V number) // Функция добавления элемента
    {
        V* tempArray;
        tempArray = new V[arraySize + 1];
        for (int i = 0; i < arraySize; i++)
        {
            tempArray[i] = arrayData[i];
        }
        delete[] arrayData;
        arrayData = tempArray;
        arraySize++;
        arrayData[arraySize - 1] = number;
    }
    void pop_front() // Функция удаления элемента
    {
        V* tempArray;
        tempArray = new V[arraySize - 1];
        for (int i = 0; i < arraySize - 1; i++)
        {
            tempArray[i] = arrayData[i + 1];
        }
        arraySize--;
        delete[] arrayData;
        arrayData = tempArray;
    }
    void pop_back()
    {
        V* tempArray;
        arraySize--;
        tempArray = new V[arraySize];
        for (int i = 0; i < arraySize; i++)
        {
            tempArray[i] = arrayData[i];
        }
        delete[] arrayData;
        arrayData = tempArray;
    }
    void pop_erase(int position)
    {
        V* tempArray;
        tempArray = new V[arraySize - 1];
        for (int i = 0; i < position; i++)
        {
            tempArray[i] = arrayData[i];
        }
        for (int i = position; i < arraySize - 1; i++)
        {
            tempArray[i] = arrayData[i + 1];
        }
        arraySize--;
        delete[] arrayData;
        arrayData = tempArray;
    }
    V* getData()
    {
        return arrayData;
    }
    int getSize()
    {
        return arraySize;
    }
    void printSize()
    {
        cout << "size\n" << arraySize << endl;
    }
};

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // исходник в UTF-8 — переключаем кодировку консоли Windows
#endif
    srand(static_cast<unsigned>(time(nullptr)));
    int variant;
    do
    {
        cout << "Выберите способ создания массива:" << "\n";
        cout << "1-вручную" << "\n";
        cout << "2-рандом" << "\n";
        cout << "Если хотите выйти нажмите 3" << "\n";
        if (!(cin >> variant))
            break;
        switch (variant)
        {
        case 1:
            manualInput();
            break;
        case 2:
            randomInput();
            break;
        case 3:
            break;
        default:
            cout << "Выберите значения 1, 2 или 3" << "\n";
            break;
        }
    } while (variant != 3);
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

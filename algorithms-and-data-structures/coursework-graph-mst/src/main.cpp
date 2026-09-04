#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "app.h"
#include "dyn_array.h"
#include "edge.h"
#include "edge_array.h"

using namespace std;

// Путь к файлу с графом по умолчанию (можно передать свой первым аргументом)
const char* DEFAULT_GRAPH_PATH = "examples/graph.txt";

string deletespaces(string sub) // удаляет из строки все пробелы, табуляции и символы возврата каретки
{
    sub.erase(remove(sub.begin(), sub.end(), '\t'), sub.end());
    sub.erase(remove(sub.begin(), sub.end(), ' '), sub.end());
    sub.erase(remove(sub.begin(), sub.end(), '\r'), sub.end());
    return sub;
}

int main(int argc, char* argv[])
{
    const string path = (argc > 1) ? argv[1] : DEFAULT_GRAPH_PATH;

    App app(path);
    if (app.run() != 0)
        return 1;

    string nodes;
    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Cannot open file " << path << endl;
        return 1;
    }
    {
        getline(file, nodes); // извлекаем первую строку из файла и записывем её в nodes
        nodes = deletespaces(nodes);
        edgeArray edgearr;
        edgeArray MOD;
        edgearr.clear();
        MOD.clear();
        int num;
        int x = 0;
        int maxx = 0;
        int y = 0;
        int MODweight = 0;
        edge temp;
        while (file >> num) // объекты класса edge будут заноситься в edgeArray
        {
            if (x > y)
            {
                if (num > 0)
                {
                    temp.from = y;
                    temp.to = x;
                    temp.weight = abs(num);
                    edgearr.add(temp);
                }
            }
            x++;
            if (x == (int)nodes.length())
            {
                if (maxx < x)
                    maxx = x;
                x = 0;
                y++;
            }
        }
        file.close();

        DynArray parents;
        parents.clear();

        for (int i = 0; i < (int)nodes.size(); i++)
        {
            parents.add(i);
        }

        edge tmp;

        for (int i = 0; i < edgearr._size(); i++) // пузырьковая сортировка весов рёбер графа
        {
            bool flag = true;
            for (int j = 0; j < edgearr._size() - i - 1; j++)
            {
                if (edgearr.getw(j) > edgearr.getw(j + 1))
                {
                    flag = false;
                    tmp = edgearr.get(j);
                    edgearr.set(j, edgearr.get(j + 1));
                    edgearr.set(j + 1, tmp);
                }
            }
            if (flag)
            {
                break;
            }
        }

        int ParF, ParS;
        for (int i = 0; (i < edgearr._size()) && (MOD._size() != (int)(nodes.size() - 1)); i++)
        {
            ParF = parents.findset(edgearr.getf(i));
            ParS = parents.findset(edgearr.gett(i));
            if (ParF != ParS)
            {
                MOD.add(edgearr.get(i));
                parents.unionset(ParF, ParS);
                MODweight += edgearr.getw(i);
            }
        }

        for (int i = 0; i < MOD._size();
             i++) // пузырьковая сортировка рёбер в минимальном остовном дереве по возрастанию первых вершин
        {
            bool flag = true;
            for (int j = 0; j < MOD._size() - i - 1; j++)
            {
                if (MOD.getf(j) > MOD.getf(j + 1))
                {
                    flag = false;
                    edge tmp = MOD.get(j);
                    MOD.set(j, MOD.get(j + 1));
                    MOD.set(j + 1, tmp);
                }
            }
            if (flag)
            {
                break;
            }
        }

        for (int i = 0; i < MOD._size(); i++)
        {
            cout << i + 1 << ". " << nodes[MOD.getf(i)] << " " << nodes[MOD.gett(i)] << endl;
        }
        if (MOD._size() != (int)(nodes.size() - 1))
            cout << "\n Warning: graph is not connected, result is a minimum spanning forest" << endl;
        cout << "\n Min route weight is:\n " << MODweight << endl;
    }
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

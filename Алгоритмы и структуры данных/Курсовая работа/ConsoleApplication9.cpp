#include <iostream>
#include <fstream>
#include <string>
#include "dynArray.h"
#include "edgeArray.h"
#include "edge.h"
#include "App.h"
#include "queueArray.h"

using namespace std;



string deletespaces(string sub) // удаляет все пробелы из строки, сдвигая все символы, не являющиеся пробелами, влево, а затем стирая лишние
{
    string::iterator end_pos = remove(sub.begin(), sub.end(), '\t');
    sub.erase(end_pos, sub.end());
    return sub;
}


int main()
{

    App app("C://Users//vitz0//oneDrive//Рабочий стол//1.txt");
    app.run();
    setlocale(0, "");
    string nodes;
    ifstream file("C://Users//vitz0//oneDrive//Рабочий стол//1.txt");
    if (file.is_open())
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
        while (!file.eof())  // объекты класса edge будут заноситься в edgeArray
        {
            file >> num;
            if (x > y)
            {
                if (num > 0) {
                    temp.from = y;
                    temp.to = x;
                    temp.weight = abs(num);
                    edgearr.add(temp);
                }
            }
            x++;
            if (x == nodes.length()) {
                if (maxx < x) maxx = x;
                x = 0;
                y++;
            }
        }
        file.close();

        DynArray parents;
        parents.clear();

        for (int i = 0; i < nodes.size(); i++)
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
            if (flag) {
                break;
            }
        }

        int ParF, ParS;
        for (int i = 0; ((i < edgearr._size()) or (MOD._size() != (nodes.size() - 1))); i++) {
            ParF = parents.findset(edgearr.getf(i));
            ParS = parents.findset(edgearr.gett(i));
            if (ParF != ParS)
            {
                MOD.add(edgearr.get(i));
                parents.unionset(ParF, ParS);
                MODweight += edgearr.getw(i);
            }
        }

        for (int i = 0; i < MOD._size(); i++) // пузырьковая сортровка рёбер в минимальном остовном дереве по возрастанию первых вершин
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
        }

        for (int i = 0; i < MOD._size(); i++)
        {
            cout << i + 1 << ". " << nodes[MOD.getf(i)] << " " << nodes[MOD.gett(i)] << endl;
        }
        cout << "\n Min route weight is:\n " << MODweight << endl;
    }
    system("pause");
    return 0;
}
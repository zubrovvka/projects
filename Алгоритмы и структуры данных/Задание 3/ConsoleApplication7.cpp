#include <iostream>
#include <vector>
#include "List.cpp"
#include "List.h"

using namespace std;

class AVLtree
{
    /*структура для представления узлов дерева*/
    struct Node
    {
        int key; //ключ узла
        Node* left; //указатель на левое поддерево
        Node* right; //указатель на правое поддерево
        int height; //высота поддерева с корнем в данном узле
    };

    Node* root;

    void makeEmpty(Node* node) //очищение дерева
    {
        if (node == nullptr)
            return;
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }

    Node* insert(int x, Node* node) //добавление узла в дерево
    {
        if (node == nullptr)
        {
            node = new Node;
            node->key = x;
            node->height = 0;
            node->left = nullptr;
            node->right = nullptr;
        }
        else if (x < node->key)
        {
            node->left = insert(x, node->left);
        }
        else if (x > node->key)
        {
            node->right = insert(x, node->right);
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        return balance(node);
    }
    Node* rightRotate(Node* node) //правый поворот
    {
        Node* u = node->left;
        node->left = u->right;
        u->right = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        u->height = max(height(u->left), node->height) + 1;
        return u;
    }

    Node* leftRotate(Node* node) //левый поворот
    {
        Node* u = node->right;
        node->right = u->left;
        u->left = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        u->height = max(height(node->right), node->height) + 1;
        return u;
    }

    Node* doubleLeftRotate(Node* node) //право-левый поворот
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    Node* doubleRightRotate(Node* node) //лево-правый поворот
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    Node* balance(Node* node) //балансировка
    {
        int balance = getBalance(node);

        if (balance < -1) //если левое поддерево больше
        {
            if (getBalance(node->left) <= 0)
            {
                return leftRotate(node); //левый поворот
            }
            else
            {
                return doubleLeftRotate(node); //право-левый поворот
            }
        }
        else if (balance > 1) //если правое поддерево больше
        {
            if (getBalance(node->right) >= 0)
            {
                return rightRotate(node); //правый поворот
            }
            else
            {
                return doubleRightRotate(node); //лево-правый поворот
            }
        }
        return node;
    }

    Node* findMin(Node* node) //поиск минимального ключа
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else if (node->left == nullptr)
        {
            return node;
        }
        else
        {
            return findMin(node->left);
        }
    }

    Node* remove(int x, Node* node) //удаление узла
    {
        Node* temp;

        /*поиск ключа*/
        if (node == nullptr)
        {
            return nullptr;
        }
        else if (x < node->key)
        {
            node->left = remove(x, node->left);
        }
        else if (x > node->key)
        {
            node->right = remove(x, node->right);
        }

        /*удаление найденного ключа*/
        else if (node->left && node->right) //два ребенка
        {
            temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->key, node->right);
        }
        else //один или 0 детей
        {
            temp = node;
            if (node->left == nullptr)
            {
                node = node->right;
            }
            else if (node->right == nullptr)
            {
                node = node->left;
            }
            delete temp;
        }
        if (node == nullptr)
        {
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        return balance(node);
    }

    Node* find(Node* node, int x) //поиск узла
    {
        if (node == nullptr || x == node->key)
        {
            return node;
        }

        if (x < node->key)
        {
            return find(node->left, x);
        }

        else
        {
            return find(node->right, x);
        }
    }

    int height(Node* node) //высота поддерева
    {
        return (node == nullptr ? -1 : node->height);
    }

    int getBalance(Node* node) //вычисление разницы высот поддеревьев
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return height(node->left) - height(node->right);
        }
    }

    void printHelper(Node* root, string indent, bool last) //вывод дерева на экран
    {
        if (root != nullptr)
        {
            cout << indent;
            if (last)
            {
                cout << "R---";
                indent += "     ";
            }
            else
            {
                cout << "L---";
                indent += "|   ";
            }

            cout << root->key << endl;

            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    void preorderPrint(Node* root)
    {
        if (root == NULL)   // Базовый случай
        {
            return;
        }
        cout << root->key << " ";
        preorderPrint(root->left);   //рекурсивный вызов левого поддерева
        preorderPrint(root->right);  //рекурсивный вызов правого поддерева
    }

    void inorderPrint(Node* root)
    {
        if (root == NULL)   // Базовый случай
        {
            return;
        }
        inorderPrint(root->left);   //рекурсивный вызов левого поддерева
        cout << root->key << " ";
        inorderPrint(root->right);  //рекурсивный вызов правого поддерева
    }

    void postorderPrint(Node* root)
    {
        if (root == NULL)   // Базовый случай
        {
            return;
        }
        postorderPrint(root->left);   //рекурсивный вызов левого поддерева
        postorderPrint(root->right);  //рекурсивный вызов правого поддерева
        cout << root->key << " ";
    }

    void bfsOrder(Node* root)
    {
        List <Node*> nodes;
        List <int> keys(1, root->key);
        if (root->left)
            nodes.push_back(root->left);
        nodes.push_back(root->right);
        int i;
        while (!nodes.empty()) {
            i = 0;
            while (i < nodes.size())
                if (nodes[i]) {
                    keys.push_back(nodes[i]->key);
                    nodes.insert(i + 1, nodes[i]->right);
                    nodes[i] = nodes[i]->left;
                    i += 2;
                }
                else
                    nodes.pop(i);
        }
        cout << keys << "\n";
    }
public:
    AVLtree()
    {
        root = nullptr;
    }

    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void search(int x)
    {
        if (find(root, x) == nullptr)
            cout << "Узел с таким ключом отстутствует" << endl;
        else
            cout << "Найден узел с таким ключом " << endl;
    }

    void print()
    {
        printHelper(root, "", true);
    }

    void PreOrder()
    {
        preorderPrint(root);
    }

    void InOrder()
    {
        inorderPrint(root);
    }

    void PostOrder()
    {
        postorderPrint(root);
    }

    void BFSOrder()
    {
        bfsOrder(root);
    }
};


int main()
{
    setlocale(LC_ALL, "ru");

    AVLtree data;
    int numbersCount; //количество
    int count;
    int t;

    cout << "\nКол-во узлов: " << endl;
    cin >> numbersCount;

    for (int i = 0; i < numbersCount; i++)
    {
        cout << "Введите элемент: " << endl;
        cin >> count;
        data.insert(count);
    }

    cout << "\nДерево выглядит следующим образом: " << endl;
    data.print();

    do
    {
        int choice = 0;
        cout << "\n~~~~~Программа~~~~~\n1. Вставка узла\n2. Поиск узла\n3. Удаление узла\n4. Preorder\n5. Inorder\n6. Postorder\n7.BFSorder\n8.  Выход\nВведите номер нужной позиции: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "\nВведите элемент, который хотите вставить в дерево: " << endl;
            cin >> count;
            data.insert(count);

            cout << "\nДерево выглядит следующим образом: " << endl;
            data.print();
            break;
        }
        case 2:
        {
            cout << "\nВведите элемент, который хотите найти: " << endl;
            cin >> count;
            data.search(count);
            break;
        }
        case 3:
        {
            cout << "\nВведите элемент, который хотите удалить: " << endl;
            cin >> count;
            data.remove(count);
            cout << "\nДерево выглядит следующим образом: " << endl;
            data.print();
            break;
        }
        case(4):
        {
            data.PreOrder();
            break;
        }
        case (5):
        {
            data.InOrder();
            break;
        }
        case(6):
        {
            data.PostOrder();
            break;
        }
        case(7):
        {
            data.BFSOrder();
            break;
        }
        case(8):
        {
            return 0;
            break;
        }
        }
        cout << "\nХотите вернуться в меню? 1 - да, 0 - нет " << endl;
        cin >> t;
    } while (t == 1);

    system("pause");
    return 0;
}
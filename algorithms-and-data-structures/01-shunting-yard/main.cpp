#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <class V> class List
{
public:
    List();
    ~List();
    void delet(int index) // удалить
    {
        if (index == 0)
        {
            deleteStart();
        }
        else
        {
            Node<V>* previous = this->head;
            for (int i = 0; i < index - 1; i++)
            {
                previous = previous->pNext;
            }

            Node<V>* toDelete = previous->pNext;

            previous->pNext = toDelete->pNext;

            delete toDelete;

            size--;
        }
    }
    void clear() // очистить
    {
        while (size)
        {
            deleteStart();
        }
    }
    void CtrlV(V value, int position) // вставить в определённую позицию
    {
        if (position == 0)
        {
            push(value);
        }
        else
        {
            if (position < 0)
            {
                cout << "Incorrect index" << endl;
                return;
            }
            Node<V>* ptr = head;
            while (position > 1)
            {
                position--;
                if (ptr->pNext == nullptr)
                {
                    cout << "Going beyond the list" << endl;
                    return;
                }
                ptr = ptr->pNext;
            }
            Node<V>* auv = new Node<V>(value);
            auv->pNext = ptr->pNext;
            ptr->pNext = auv;
            size++;
        }
    }
    void PushBack(V value) // положить на вершину стека
    {
        Node<V>* ptrN = new Node<V>(value);
        if (this->head == NULL)
            this->head = ptrN;
        else
        {
            ptrN->pNext = this->head;
            this->head = ptrN;
        }
        size++;
    }
    void deleteStart() // удалить из начала
    {
        Node<V>* temp = head;
        head = head->pNext;
        delete temp;
        size--;
    }
    void push(V data) //  вставить в начало
    {
        head = new Node<V>(data, head);
        size++;
    }
    void deleteBack() //  удалить с конца
    {
        Node<V>* ptrN;
        if (this->head != NULL)
        {
            ptrN = this->head;
            this->head = ptrN->pNext;
            delete ptrN;
            ptrN = nullptr;
            size--;
        }
    }
    int getSize() //   размер
    {
        return size;
    }
    void delete_insert(int position) // удаление элемента с определенной позиции
    {
        if (position < 0)
        {
            cout << "Incorrect index\n";
            return;
        }
        if (position == 0)
        {
            deleteStart();
            return;
        }
        Node<V>* ptr = head;
        while (position > 1)
        {
            position--;
            if (ptr->pNext == nullptr)
            {
                cout << "Going beyond the list " << endl;
                return;
            }
            ptr = ptr->pNext;
        }
        Node<V>* auv = ptr->pNext;
        if (auv == nullptr)
        {
            cout << "Going beyond the list " << endl;
            return;
        }
        ptr->pNext = auv->pNext;
        delete auv;
        size--;
    }

    V& operator[](const int index);

    template <class U> class Node
    {
    public:
        Node* pNext;
        U data;

        Node(U data = U(), Node* pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };

    Node<V>* head;

    Node<V>* get_head()
    {
        return this->head;
    }

    int size;
};

template <class V> List<V>::List()
{
    size = 0;
    head = nullptr;
}

template <class V> List<V>::~List()
{
    clear();
}

template <class V> V& List<V>::operator[](const int index)
{
    int counter = 0;
    Node<V>* current = this->head;

    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
    throw out_of_range("List index out of range");
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
    dynamic_array(int size) // Создание массива заданного размера
    {
        arraySize = size;
        if (arraySize != 0)
            arrayData = new V[arraySize];
        else
            arrayData = 0;
    }
    ~dynamic_array()
    {
        delete[] arrayData;
    }
    dynamic_array(const dynamic_array&) = delete;
    dynamic_array& operator=(const dynamic_array&) = delete;
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

    V& operator[](int i)
    {
        return arrayData[i];
    }
};

template <class V> ostream& operator<<(ostream& out, dynamic_array<V>& arr)
{
    for (int i = 0; i < arr.getSize(); ++i)
        out << arr[i] << " ";
    return out;
}

class Operators
{
public:
    string op;
    int priority_op;
};

int main()
{
    Operators op[7];
    op[0].op = "+";
    op[0].priority_op = 0;

    op[1].op = "-";
    op[1].priority_op = 0;

    op[2].op = "*";
    op[2].priority_op = 1;

    op[3].op = "/";
    op[3].priority_op = 1;

    op[4].op = "^";
    op[4].priority_op = 2;

    op[5].op = "sin";
    op[5].priority_op = 3;

    op[6].op = "cos";
    op[6].priority_op = 3;

    Operators left_bracket;
    left_bracket.op = "(";

    Operators right_bracket;
    right_bracket.op = ")";

    List<Operators> stackOp;
    string input;

    int position = 0;
    string buff;
    string temp;

    int flag;
    int positionOp;

    dynamic_array<string> yard(0);

    cout << "Enter the given expression (each character separated by a space)" << endl;
    getline(cin, input);

    cout << "Working with a List - 0" << endl;
    cout << "Working with an array - 1" << endl;

    int number = 0;
    cin >> number;
    if (number > 1 || number < 0)
    {
        cout << "error: unknown mode" << endl;
        return 1;
    }

    if (number == 0)
    {
        while (input != "")
        {
            position = input.find(" ");

            if (position == -1)
            {
                position = 1;
                buff = input.substr(0, position);
                input = "";
            }
            else
            {
                buff = input.substr(0, position);
                input = input.substr(position + 1, input.length());
            }

            flag = 0;
            positionOp = 0;

            while ((flag == 0) && (positionOp <= 6))
            {
                if (buff == op[positionOp].op)
                {
                    flag = 1;
                }
                else
                {
                    positionOp++;
                }
            }

            if (flag == 1)
            {
                if (stackOp.get_head() == NULL)
                {
                    stackOp.PushBack(op[positionOp]);
                }
                else
                {
                    while (stackOp.get_head() != NULL && stackOp.get_head()->data.op != "(")
                    {
                        if (stackOp.get_head()->data.priority_op >= op[positionOp].priority_op)
                        {
                            cout << stackOp.get_head()->data.op << " ";
                            stackOp.deleteBack();
                        }
                        else
                            break;
                    }
                    stackOp.PushBack(op[positionOp]);
                }
            }
            else
            {
                if (buff == "(")
                {
                    stackOp.PushBack(left_bracket);
                }
                else if (buff == ")")
                {
                    while (stackOp.get_head()->data.op != "(")
                    {
                        cout << stackOp.get_head()->data.op << " ";
                        stackOp.deleteBack();
                    }
                    stackOp.deleteBack();
                }
                else
                    cout << buff << " ";
            }
        }

        while (stackOp.get_head() != NULL)
        {
            cout << stackOp.get_head()->data.op << " ";
            stackOp.deleteBack();
        }
    }

    if (number == 1)
    {
        while (input != "")
        {
            position = input.find(" ");

            if (position == -1)
            {
                position = 1;
                buff = input.substr(0, position);
                input = "";
            }
            else
            {
                buff = input.substr(0, position);
                input = input.substr(position + 1, input.length());
            }

            flag = 0;
            positionOp = 0;

            while ((flag == 0) && (positionOp <= 6))
            {
                if (buff == op[positionOp].op)
                {
                    flag = 1;
                }
                else
                {
                    positionOp++;
                }
            }
            if (flag == 1)
            {
                if (stackOp.get_head() == NULL)
                {
                    stackOp.PushBack(op[positionOp]);
                }
                else
                {
                    while (stackOp.get_head() != NULL && stackOp.get_head()->data.op != "(")
                    {
                        if (stackOp.get_head()->data.priority_op >= op[positionOp].priority_op)
                        {
                            temp = stackOp.get_head()->data.op;
                            yard.push_back(temp);
                            stackOp.deleteBack();
                        }
                        else
                            break;
                    }
                    stackOp.PushBack(op[positionOp]);
                }
            }
            else
            {
                if (buff == "(")
                    stackOp.PushBack(left_bracket);
                else if (buff == ")")
                {
                    while (stackOp.get_head()->data.op != "(")
                    {
                        temp = stackOp.get_head()->data.op;
                        yard.push_back(temp);
                        stackOp.deleteBack();
                    }
                    stackOp.deleteBack();
                }
                else
                {
                    temp = buff;
                    yard.push_back(temp);
                }
            }
        }
        while (stackOp.get_head() != NULL)
        {
            temp = stackOp.get_head()->data.op;
            yard.push_back(temp);
            stackOp.deleteBack();
        }
        for (int i = 0; i < yard.getSize(); i++)
        {
            cout << yard[i] << " ";
        }
    }
    cout << endl;

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

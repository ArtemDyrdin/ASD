#include <iostream>
#include <string>
#include "windows.h"

using namespace std;
struct Node // узел
{
    int data;
    Node* r; // указатель на правого потомка
    Node* l; // указатель на левого потомка

    explicit Node(int v) : data(v), l(nullptr), r(nullptr) {} //конструктор
};

class Tree
{
private:
    Node* p; // указатель на корень дерева
    string reformance(Node* node) // преобразование дерева в линейно скобочную последовательность
    {
        if (node == nullptr)
        {
            return "";
        }
        string result =  to_string(node->data); //текущий узел

        if (node->l != nullptr || node->r != nullptr) // проверяем наличие потомков
        {
            if (node->l != nullptr)
            {
                result += "(" + reformance(node->l) + ")";
            }
            if (node->r != nullptr)
            {
                result += "(" + reformance(node->r) + ")";
            }
        }
        return result;
    }

    Node* addVal(Node* node, int v) // функция добавления нового значения
    {
        if (node == nullptr)
            return new Node(v); // создаем новый узел и делаем его корнем
        if (v < node->data) // для левого поддерева
            node->l = addVal(node->l, v);
        else if (v > node->data)
            node->r = addVal(node->r, v);
        return node;
    }

    Node* minVal(Node* node) // поиск минимального значения в дереве
    {
        while (node->l != nullptr)
        {
            node = node->l;
        }
        return node;
    }

    Node* maxVal(Node* node) // поиск максимального значения в дереве
    {
        while (node->r != nullptr)
            node = node->r;
        return node;
    }

    bool searchVal(Node* node, int v) // поиск значения в дереве
    {
        if (node == nullptr)
            return false;
        if (v == node->data)
            return true;
        else if (v < node->data)
            return searchVal(node->l, v);
        else
            return searchVal(node->r, v);
    }

    Node* removeVal(Node* node, int v) // удаление заданного значения в дереве
    {
        if (node == nullptr)
            return node;

        if (v < node->data)
            node->l = removeVal(node->l, v);
        else if (v > node->data)
            node->r = removeVal(node->r, v);
        else
        {
            if (node->l == nullptr)
            {
                Node* temp = node->r;
                delete node;
                return temp;
            }
            else if (node->r == nullptr)
            {
                Node* temp = node->l;
                delete node;
                return temp;
            }

            Node* temp = minVal(node->r);
            node->data = temp->data;
            node->r = removeVal(node->r, temp->data);
        }
        return node;
    }

public:
    Tree() : p(nullptr) {};

    void Add(int v)
    {
        p = addVal(p, v);
    }
    int Min()
    {
        return minVal(p)->data;
    }
    int Max()
    {
        return maxVal(p)->data;
    }
    void Remove(int v)
    {
        p = removeVal(p, v);
    }
    bool Search(int v)
    {
        return searchVal(p, v);
    }
    void printTree()
    {
        cout << "Tree: " << reformance(p) << endl;
    }

};


int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Tree tree;
    string s = "8(3(1)(6(7)(4)))(10(14)(13))";
    int ind = 0;
    while (ind < s.length()) //проход по строке и преобразование ее в бинарное дерево
    {
        bool flag = false;
        int v = 0;
        while ((s[ind] - '0') >= 0 and (s[ind] - '0') <= 9)
        {
            flag = true;
            v *= 10;
            v += s[ind] - '0';
            ind += 1;
        }
        if (flag)
        {
            tree.Add(v);
        }

        ind += 1;
    }

    cout << "текущее дерево: ";
    tree.printTree();
    cout << "Max: " << tree.Max() << endl;
    cout << "Min: " << tree.Min() << endl;
    tree.Remove(1);
    cout << "1?: " << tree.Search(1) <<  endl;
    tree.printTree();
    tree.Add(5);
    tree.printTree();
}
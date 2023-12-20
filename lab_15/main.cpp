#include <iostream>
#include <string>
#include <vector>

class Tree
{
public:
    int m_value{}; // значение узла
    Tree* p{}; // родительский узел
    Tree* l{}; // левый потомок
    Tree* r{}; // правый потомок
    std::string input_value;

    // Конструктор
    Tree(const int v, Tree* parent)
    {
        m_value = v;
        p = parent;
    }


    Tree() = default;

    // Функция добавления нового узла в дерево
    void add(const int v) {
        if (v > m_value) {
            if (r == nullptr)
                r = new Tree(v, this);
            else
                r->add(v);
        }
        else {
            if (l == nullptr)
                l = new Tree(v, this);
            else
                l->add(v);
        }
    }

    // Функция перевода числа в строку
    static std::string toString(int value)
    {
        std::string result;

        if (value > 9)
        {
            result += char(value / 10 + 48);
            result += char(value % 10 + 48);
        }
        else
            result += char(value + 48);

        return result;
    }

    // Преобразование дерева в линейно скобочную последовательность посредством рекурсии
    void print(Tree* tree)
    {
        input_value += toString(tree->m_value);
        if (tree->l != nullptr || tree->r != nullptr) // проверяем имеет ли текущий узел поддеревья
        {
            input_value += '(';
            if (tree->l != nullptr)
                print(tree->l);
            input_value += ',';
            if (tree->r != nullptr)
                print(tree->r);
            input_value += ')';
        }

    }

    void Print()
    {
        print(this);
    }

    // проверяем является ли символ числом
    static bool isDigital(const char elem)
    {
        return (elem >= '0' && elem <= '9');
    }

    // Функция для прохода по строке и преобразования ее в бинарное дерево
    static Tree parse(std::string str)
    {
        Tree result;
        int index;

        if (isDigital(str[0]) && isDigital(str[1]))
        {
            int val = (str[0] - 48) * 10 + str[1] - 48;
            result.m_value = val;
            index = 2;
        }
        else {
            int val = str[0] - 48;
            result.m_value = val;
            index = 1;
        }
        for (int i = index; i < str.size() - 1;) // если символы являются числами добавляем в дерево
        {
            if (isDigital(str[i]) && isDigital(str[i + 1]))
            {
                int value = (str[i] - 48) * 10 + str[i + 1] - 48;
                result.add(value);
                i += 2;
            }
            else if (isDigital(str[i]) && !isDigital(str[i + 1]))
            {
                int value = str[i] - 48;
                result.add(value);
                i++;
            }
            else
            {
                i++; // если символ не число, переходим к следующему
            }
        }

        return result;
    }
};

//прямой обход
void Direct(std::vector <int>& v, const Tree* tree)
{
    if (tree != nullptr)
    {
        v.push_back(tree->m_value);
        Direct(v, tree->l);
        Direct(v, tree->r);
    }
}

//центральный обход
void Centeral(std::vector<int>& v, const Tree* tree)
{
    if (tree != nullptr)
    {
        Centeral(v, tree->l);
        v.push_back(tree->m_value);
        Centeral(v, tree->r);
    }
}

//концевой обход
void Reverse(std::vector<int>& v, const Tree* tree)
{
    if (tree != nullptr)
    {
        Reverse(v, tree->l);
        Reverse(v, tree->r);
        v.push_back(tree->m_value);
    }
}


int main()
{
    std::vector <int> dV;
    std::vector <int> cV;
    std::vector <int> rV;
    std::string input = "8(3(1,6(4,7)),10(,14(13,)))"; // линейно скобочная последовательность
    Tree tree;
    tree = Tree::parse(input);
    Tree newTree = tree;
    newTree.Print();

    Direct(dV, &newTree);
    Centeral(cV, &newTree);
    Reverse(rV, &newTree);

    std::cout << "Direct order:" << std::endl;
    for (auto& value : dV)
        std::cout << value << "\t";
    std::cout << std::endl;

    std::cout << "Central order:" << std::endl;
    for (auto& value : cV)
        std::cout << value << "\t";
    std::cout << std::endl;

    std::cout << "Reverse order:" << std::endl;
    for (auto& value : rV)
        std::cout << value << "\t";
    std::cout << std::endl;
    system("pause");
}
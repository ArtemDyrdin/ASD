#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>

class Tree
{
public:
	int m_value{};
	Tree* p{};
	Tree* l{};
	Tree* r{};
	std::string input_value;

	Tree(const int v, Tree* parent) {
        m_value = v;
		p = parent;
	}

	Tree() = default;

	explicit Tree(std::string str) {
        input_value = std::move(str);
	}

    // Функция добавления{}
	void add(const int v) {
		if (v > m_value) {
			if (r == nullptr) {
				r = new Tree(v, this);
			}
			else {
				r->add(v);
			}
		}
		else {
			if (l == nullptr) {
				l = new Tree(v, this);
			}
			else {
				l->add(v);
			}
		}
	}


    // Функция перевода числа в строку
	static std::string toString(int value)
	{
		std::string result;

		if (value > 9) {
			result += char(value / 10 + 48);
			result += char(value % 10 + 48);
		}
		else {
			result += char(value + 48);
		}

		return result;
	}

    // Преобразование дерева в линейно скобочную последовательность
	void print(Tree* tree)
	{
        input_value += toString(tree->m_value);
		if (tree->l != nullptr || tree->r != nullptr)
		{
            input_value += '(';
			if (tree->l != nullptr)
			{
				print(tree->l);
			}
            input_value += ',';
			if (tree->r != nullptr)
			{
				print(tree->r);
			}
            input_value += ')';
		}

	}


	void Print()
	{
		print(this);
	}

    // проверка на число
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


		for (int i = index; i < str.size() - 1;)
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
				i++;
			}
		}

		return result;
	}
};

// прямой обход
void Direct(std::vector<int>& v, const Tree* tree)
{
	if (tree == nullptr)
		return;
	std::stack<const Tree*> stack;
	stack.push(tree);
	while (!stack.empty())
	{
		const Tree* node = stack.top(); // достаем верхний узел из стека
		stack.pop();
		v.push_back(node->m_value);
		if (node->r != nullptr) // если у узла есть правый потомок,то добавляем его в стек
		{
			stack.push(node->r);
		}
		if (node->l != nullptr)
		{
			stack.push(node->l);
		}
	}
}

// центральный обход
void Centeral(std::vector<int>& v, const Tree* tree)
{
	if (tree != nullptr)
	{
		Centeral(v, tree->l);
		v.push_back(tree->m_value);
		Centeral(v, tree->r);
	}
}

// концевой обход
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
	int maxElem;
	std::string str = "8(3(1,6(4,7)),10(,14(13,)))"; // линейно скобочная послед
	Tree tree;
	tree = Tree::parse(str);
	Tree newTree = tree;
	newTree.Print();

	Direct(dV, &newTree);
	Centeral(cV, &newTree);
	Reverse(rV, &newTree);

	std::cout << "Direct order:" << std::endl;
	for (auto& value : dV) {
		std::cout << value << "\t";
	}
	std::cout << std::endl;

    // Выводим центральный обход
	std::cout << "Central order:" << std::endl;
	for (auto& value : cV) {
		std::cout << value << "\t";
	}
	std::cout << std::endl;

    // Выводим концевой обход
	std::cout << "Reverse order:" << std::endl;
	for (auto& value : rV) {
		std::cout << value << "\t";
	}
	std::cout << std::endl;
}
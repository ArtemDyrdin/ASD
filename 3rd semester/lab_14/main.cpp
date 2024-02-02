#include <iostream>
#include <fstream>
#include <vector>

int hash(std::string s, int table_size) //вычисляем хеш - значение
{
    int hash = 0;
    for (char & i : s)
        hash += (int)i;
    hash = hash % table_size;
    return hash;
}


void fill_with_lists(std::vector<std::vector<std::string>>& table, const std::string& str) // заполняет двумерный вектор
{
    int ind = hash(str, static_cast<int>(table.size()));
    table[ind].push_back(str);
}


int main()
{
    std::ifstream in;
    //размер таблицы
    in.open("input.txt");
    std::string a;
    int size = 0;
    while (in >> a)
    {
        size++;
    }
    in.close();

    //двумерный вектор заданного размера для таблицы со списками
    std::vector<std::vector<std::string>> table;
    table.reserve(size);
    for (int i = 0; i < size; i++)
        table.emplace_back();

    // заполнение хеш таблиц
    in.open("input.txt");
    std::string cur;
    while (in >> cur)
    {
        fill_with_lists(table, cur);
    }
    in.close();


    std::ofstream out2;
    out2.open("output1.txt");

    for (int i = 0; i < size; i++)
    {
        out2 << i << "   ";
        for (const auto & j : table[i])
            out2 << j << "  ";
        out2 << '\n';
    }

    out2.close();

    system("pause");
}
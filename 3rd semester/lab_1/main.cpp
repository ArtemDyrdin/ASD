#include <iostream>
#include <windows.h>
#include "vector"

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::string brackets; // строка из введенных скобок
    std::vector<char> stack; // стек
    char paired_brackets[6] = {'(', ')', '{', '}', '[', ']'}; // парные скобки

    std::cout << "Введите строку: ";
    std::cin >> brackets;

    // заполняем стек и убираем из него рядом стоящие скобки
    stack.push_back(brackets[0]);
    for (int i = 1; i < brackets.length(); i++) {
        stack.push_back(brackets[i]);

        // удаляем парные скобки из стека
        for (int first_bracket = 0; first_bracket < 5; first_bracket += 2)
            if (stack[stack.size() - 2] == paired_brackets[first_bracket] && \
                stack[stack.size() - 1] == paired_brackets[first_bracket + 1]) {
                stack.pop_back();
                stack.pop_back();
            }
    }

    if (stack.empty())
        std::cout << "Строка существует" << std::endl;
    else
        std::cout << "Строка не существует" << std::endl;

    return 0;
}

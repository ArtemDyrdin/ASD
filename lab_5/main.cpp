#include <iostream>
#include <vector>

// функция - Сортировка Вставками
void insertionSort(std::vector<int>& numbers) {
    // выбираем элемент и меняем его с предыдущими, пока он меньше их
    for (int i = 1; i < numbers.size(); i++)
        for (int j = i; j > 0; j--)
            if (numbers[j-1] > numbers[j])
                std::swap(numbers[j-1], numbers[j]);
            else
                break;
}

int main() {
    std::vector<int> numbers = {2342, 22, 5, 78, 1000, 664211, 1}; // заданная последовательность
    insertionSort(numbers); // сортировка последовательности

    // вывод элементов последовательности
    for (int i : numbers)
        std::cout << i << "  ";
    std::cout << std::endl;

    return 0;
}

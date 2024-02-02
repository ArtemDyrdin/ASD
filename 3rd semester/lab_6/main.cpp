#include <iostream>
#include <vector>

// функция - Сортировка Посредством Выбора
void selectionSort(std::vector<int>& numbers) {
    // выбираем минимальный элемент и элемент меньше, после чего меняем их местами
    for (int i = 0; i < numbers.size() - 1; i++) {
        int minimal = i;
        for (int j = i + 1; j < numbers.size(); j++)
            if (numbers[j] < numbers[minimal])
                minimal = j;
        std::swap(numbers[minimal], numbers[i]);
    }
}

// функция вывода элементов последовательности
void showNumbers(std::vector<int>& numbers) {
    for (int i : numbers)
        std::cout << i << "  ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {1324, 983, 3, 6, 77765, 2}; // последовательность элементов
    selectionSort(numbers); // сортировать последовательность
    showNumbers(numbers); // вывести элементы последовательности
    return 0;
}

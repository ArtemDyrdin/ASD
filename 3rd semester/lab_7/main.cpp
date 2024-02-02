#include <iostream>
#include "vector"

// сортировка Шелла
void ShellSort(std::vector<int>& numbers) {
    int last_index = static_cast<int>(numbers.size()); // индекс последнего элемента
    int step = static_cast<int>(numbers.size())/2; // шаг

    while (step > 0) { // пока шаг больше нуля
        for (int i = step; i < last_index; i++) {
            int j = i;
            int delta = j - step;
            while (delta >= 0 && numbers[delta] > numbers[j]) {
                std::swap(numbers[delta], numbers[j]);
                j = delta;
                delta = j - step;
            }
        }
        step /= 2;
    }
}

// вывод элементов std::vector<int>
void showElements(std::vector<int>& numbers) {
    for (int i : numbers)
        std::cout << i << "  ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {23, 33, 1, 9, 555, 0}; // изначальная последовательность
    ShellSort(numbers); // сортируем последовательность
    showElements(numbers); // выводим отсортированную последовательность
    return 0;
}

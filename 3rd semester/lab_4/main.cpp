#include <iostream>
#include <vector>


// функция - Сортировка Методом Прочесывания (Расческой)
void combSort(std::vector<int>& numbers) {
    int step = static_cast<int>(numbers.size()); // количество элементов последовательности
    double factor = 1.247; // оптимальное число для вычисления шага сравнения

    // пока шаг последовательности больше единицы
    while (step > 1) {
        step = static_cast<int>(step / factor); // текущий шаг последовательности

        // сравнение и замена элементов последовательности на расстоянии step
        int i = 0;
        while (i + step < numbers.size()) {
            if (numbers[i] > numbers[i + step])
                std::swap(numbers[i], numbers[i + step]);
            i++;
        }
    }
}

int main() {
    std::vector<int> numbers = {3245, 33, 89, 1, 5, 10000}; // изначальная последовательность
    combSort(numbers); // сортировка последовательности

    // вывод элементов последовательности
    for (int num : numbers)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
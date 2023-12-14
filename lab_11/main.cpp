#include <iostream>
#include <vector>

// Вывести эл-ты std::vector<int>
void showElements(std::vector<int>& numbers) {
    for (int num : numbers)
        std::cout << num << " ";
    std::cout << std::endl;
}

// Быстрая сортировка
void quickSort(std::vector<int>& numbers, int left, int right) {
    // Если индекс левого эл-та меньше правого
    if (left < right) {
        int pivot = numbers[(left + right) / 2]; // средний эл-т
        int i = left, j = right; // перезаписывает индекс левого и правого эл-тов

        // Эл-ты меньше среднего помещаем вправо, эл-ты больше - влево
        while (i <= j) {
            while (numbers[i] < pivot)
                i++;
            while (numbers[j] > pivot)
                j--;
            if (i <= j) {
                std::swap(numbers[i], numbers[j]);
                i++;
                j--;
            }
        }
        // Проводим ту же операцию с левой и правой частями
        quickSort(numbers, left, j);
        quickSort(numbers, i, right);
    }
}

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 6, 4, 3, 7, 8}; // исходная послед-ть
    showElements(numbers);

    quickSort(numbers, 0, static_cast<int>(numbers.size()) - 1); // сортируем послед-ть
    showElements(numbers);
    return 0;
}

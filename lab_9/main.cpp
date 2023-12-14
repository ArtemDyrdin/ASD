#include <iostream>
#include <vector>

// Преобразовать в двоичную кучу поддерево с корнем под индексом i
void heapify (std::vector<int>& numbers, int n, int i) {
    int largest = i; // наибольший элемент поддерева
    int left = 2*i + 1; // элемент слева
    int right = 2*i + 2; // элемент справа

    // Определяем наибольший элемент среди левого и правого элемента
    if (left < n && numbers[left] > numbers[largest])
        largest = left;
    if (right < n && numbers[right] > numbers[largest])
        largest = right;

    // Меняем местами корень с наибольшим элементом, если они не равны, и подымаемся вверх по дереву
    if (largest != i) {
        std::swap(numbers[i], numbers[largest]);
        heapify(numbers, n, largest);
    }
}

// Пирамидальная сортировка
void heapSort(std::vector<int>& numbers) {
    // Строим дерево в двоичной куче
    for (int i = static_cast<int>(numbers.size()) / 2 - 1; i >= 0; i--)
        heapify(numbers, static_cast<int>(numbers.size()), i);
    // Извлекаем элементы с конца и записываем максимальные элементы в конец
    for (int i = static_cast<int>(numbers.size()) - 1; i >= 0; i--) {
        std::swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
}

// Вывести элементы последовательности
void showElements(std::vector<int>& numbers) {
    for (int number : numbers)
        std::cout << number << "  ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers = {23, 23492, 0, 12121212, 7, 235, 444, 9876, 2, 1, 399}; // последовательность чисел
    showElements(numbers); // выводим последовательность
    heapSort(numbers); // сортируем последовательность
    showElements(numbers); // выводим отсортированную последовательность
    return 0;
}
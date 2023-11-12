#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "windows.h"

// вывод элементов std::vector<int>
void showElements(std::vector<int>& numbers) {
    for (int i : numbers)
        std::cout << i << "  ";
    std::cout << std::endl;
}

// вывод элементов std::vector<int>
void showElements(std::vector<std::vector<int>>& bins, int base) {
    for (int i = 0; i < base; i++) {
        std::cout << '{';
        for (int q: bins[i])
            std::cout << q << "  ";
        std::cout << "}  ";
    }
    std::cout << std::endl;
}

// Поразрядная сортировка
void radixSort(std::vector<int>& numbers) {
    int max = *max_element(numbers.begin(), numbers.end());
    int max_number_length = static_cast<int>(std::to_string(max).size()); // разряд наибольшего числа в массиве
    const int base = 10; // основание системы счисления

    std::vector<std::vector<int>> bins(base, std::vector<int>(0)); // промежуточный массив из base-пустых массивов

    // перебираем все разряды, начиная с 0
    for (int i = 0; i < max_number_length; i++) {
        std::cout << "Разряд: " << i << std::endl;
        for (int j: numbers) {
            int digit = static_cast<int>((j / pow(base, i))) % base; // цифра, стоящая на текущем разряде
            bins[digit].push_back(j); // отправляем число в элемент промежуточного массива по индексу равному значению этой цифры
        }
        numbers.clear(); // очищаем исходный массив

        // записываем в исходный массив все ненулевые элементы промежуточного массива
        for (auto & bin : bins)
            for (int j : bin)
                numbers.push_back(j);

        showElements(numbers); // выводим исходный массив
        showElements(bins, base); // выводим промежуточный массив

        // очищаем элементы промежуточного массива
        for (auto & bin : bins)
            bin = std::vector<int>(0);
    }
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::vector<int> numbers = {0, 1111111, 222, 4444444, 45, 999999999}; // последовательность чисел
    radixSort(numbers); // сортируем поразрядно

    std::cout << std::endl << "Отсортированная последовательность:" << std::endl;
    showElements(numbers); // выводим отсортированную последовательность
    return 0;
}

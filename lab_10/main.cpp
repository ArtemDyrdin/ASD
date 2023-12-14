#include <iostream>
#include <vector>
#include <windows.h>

// Слияние
void merge(std::vector<int>& arr, int l, int middle, int r) {
    int n1 = middle - l + 1; // индекс эл-та слева
    int n2 = r - middle; // индекс эл-та посередине

    std::vector<int> L(n1); // массив из n1 эл-ов левой части
    std::vector<int> R(n2); // массив из n2 эл-ов правой части

    // Добавляем в массив левой части эл-ты из левой части
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    // Добавляем в массив правой части эл-ты из правой части
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    int i = 0; // индекс эл-та левой части
    int j = 0; // индекс эл-та правой части
    int k = l; // индекс текущего эл-та

    // Сравниваем эл-ты
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Переписываем левую часть исходного массива
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Переписываем правую часть исходного массива
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Сортировка слиянием
void mergeSort(std::vector<int>& arr, int l, int r) {
    // Если начальный индекс меньше конечного
    if (l < r) {
        int middle = l + (r - l) / 2; // средний индекс

        mergeSort(arr, l, middle); // сортируем левую часть
        mergeSort(arr, middle + 1, r); // сортируем правую часть

        merge(arr, l, middle, r); // сливаем отсортированные массивы, сравнивая их
    }
}

int main() {


    std::vector<int> arr = {12, 11, 13, 5, 6, 7}; // исходная послед-ть эл-ов

    const int arr_size = static_cast<int>(arr.size()); // размер послед-ти

    std::cout << "Given array is \n";
    for (int i = 0; i < arr_size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, arr_size - 1);

    std::cout << "Sorted array is \n";
    for (int i = 0; i < arr_size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
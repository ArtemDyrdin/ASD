#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Реализация алгоритма Крускала
void KruskalMST(vector<vector<int>>& graph, int V, const string& outputFile) {
    // Результаты минимального покрывающего дерева
    vector<pair<int, int>> result;

    // Проходим по всем вершинам и ребрам, создаем список ребер
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < V; ++i)
        for (int j = i + 1; j < V; ++j)
            if (graph[i][j] != 0)
                edges.push_back({graph[i][j], {i, j}});

    // Сортируем ребра по весу
    sort(edges.begin(), edges.end());

    // Создаем массив подмножеств для операции объединения
    vector<int> parent(V);
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    int minimumCost = 0;

    // Проходим по всем ребрам в отсортированном списке
    for (auto edge : edges) {
        int weight = edge.first;
        int src = edge.second.first;
        int dest = edge.second.second;

        // Находим корневые вершины src и dest
        while (parent[src] != src)
            src = parent[src];
        while (parent[dest] != dest)
            dest = parent[dest];

        // Если корневые вершины не совпадают, добавляем ребро к результату
        if (src != dest) {
            result.emplace_back(src, dest);
            minimumCost += weight;
            parent[src] = dest;
        }
    }

    // Выводим результат в файл
    ofstream outFile(outputFile);
    if (!outFile) {
        cout << "Ошибка открытия файла для записи";
        return;
    }

    for (auto edge : result) {
        outFile << edge.first << " - " << edge.second << endl;
    }

    outFile << "Общий вес минимального покрывающего дерева: " << minimumCost << endl;

    outFile.close();
}

int main() {
    string inputFile = "input.txt"; // Имя файла с входными данными
    string outputFile = "output.txt"; // Имя файла для записи результата

    ifstream inFile(inputFile);
    if (!inFile) {
        cout << "Open file ERROR";
        return 1;
    }

    int V;
    inFile >> V; // Читаем количество вершин

    // Читаем матрицу смежности из файла
    vector<vector<int>> graph(V, vector<int>(V));
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            inFile >> graph[i][j];

    inFile.close();

    KruskalMST(graph, V, outputFile);

    cout << "MST in " << outputFile << endl;

    return 0;
}
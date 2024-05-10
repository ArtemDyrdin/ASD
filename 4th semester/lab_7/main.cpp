#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Реализация алгоритма Прима
void PrimMST(vector<vector<int>>& graph, int V, const string& outputFile) {
    // Создаем вектор для хранения ключей вершин (минимальных весов ребер)
    vector<int> key(V, INF);
    // Создаем вектор для хранения родительских вершин в минимальном остовном дереве
    vector<int> parent(V, -1);
    // Создаем вектор для хранения информации о том, включена ли вершина в остовное дерево
    vector<bool> inMST(V, false);

    // Выбираем первую вершину в качестве начальной
    key[0] = 0;

    // Построение остовного дерева
    for (int count = 0; count < V - 1; ++count) {
        // Находим вершину с минимальным ключом, которая еще не включена в остовное дерево
        int minKey = INF, minIndex;
        for (int v = 0; v < V; ++v)
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }

        // Включаем выбранную вершину в остовное дерево
        inMST[minIndex] = true;

        // Обновляем ключи и родительские вершины смежных вершин
        for (int v = 0; v < V; ++v)
            if (graph[minIndex][v] && !inMST[v] && graph[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = graph[minIndex][v];
            }
    }

    // Записываем результат в файл
    ofstream outFile(outputFile);
    if (!outFile) {
        cout << "Ошибка открытия файла для записи";
        return;
    }

    int minimumCost = 0;
    for (int i = 1; i < V; ++i) {
        outFile << parent[i] << " - " << i << " : " << graph[i][parent[i]] << endl;
        minimumCost += graph[i][parent[i]];
    }

    outFile << "Общий вес минимального покрывающего дерева: " << minimumCost << endl;

    outFile.close();
}

int main() {
    string inputFile = "input.txt"; // Имя файла с входными данными
    string outputFile = "output.txt"; // Имя файла для записи результата

    ifstream inFile(inputFile);
    if (!inFile) {
        cout << "Open File ERROR";
        return 1;
    }

    int V;
    inFile >> V; // Читаем количество вершин

    // Читаем матрицу смежности из файла
    vector<vector<int>> graph(V, vector<int>(V));
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j) {
            inFile >> graph[i][j];
        }

    inFile.close();

    PrimMST(graph, V, outputFile);

    cout << "MST in " << outputFile << endl;

    return 0;
}

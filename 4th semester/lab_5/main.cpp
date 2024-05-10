#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Обход графа в глубину для получения списка вершин в порядке завершения их поиска
void DFS(vector<vector<int>>& graph, int v, vector<bool>& visited, stack<int>& finishedStack) {
    visited[v] = true;

    // Перебор смежных вершин
    for (int i = 0; i < graph.size(); ++i)
        if (graph[v][i] == 1 && !visited[i])
            DFS(graph, i, visited, finishedStack);

    // Добавляем текущую вершину в стек
    finishedStack.push(v);
}

// Обход графа в глубину для поиска сильно связных компонент
void DFSReverse(vector<vector<int>>& graph, int v, vector<bool>& visited, vector<int>& scc) {
    visited[v] = true;
    scc.push_back(v);

    // Перебор смежных вершин
    for (int i = 0; i < graph.size(); ++i)
        if (graph[i][v] == 1 && !visited[i])
            DFSReverse(graph, i, visited, scc);
}

// Транспонирование графа
vector<vector<int>> transposeGraph(vector<vector<int>>& graph) {
    int n = static_cast<int>(graph.size());
    vector<vector<int>> transposed(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            transposed[i][j] = graph[j][i];

    return transposed;
}

// Нахождение сильно связных компонент
void KosarajuSharirSCC(vector<vector<int>>& graph, vector<vector<int>>& sccList) {
    int n = static_cast<int>(graph.size());
    vector<bool> visited(n, false);
    stack<int> finishedStack;

    // Обход графа в глубину для получения списка вершин в порядке завершения их поиска
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            DFS(graph, i, visited, finishedStack);

    // Транспонирование графа
    vector<vector<int>> transposedGraph = transposeGraph(graph);

    // Сброс меток посещения
    fill(visited.begin(), visited.end(), false);

    // Обработка вершин в порядке завершения их поиска
    while (!finishedStack.empty()) {
        int v = finishedStack.top();
        finishedStack.pop();

        if (!visited[v]) {
            vector<int> scc;
            DFSReverse(transposedGraph, v, visited, scc);
            sccList.push_back(scc);
        }
    }
}

int main() {
    // Чтение графа из файла
    ifstream input("graph.txt");
    if (!input) {
        cerr << "Unable to open file";
        return 1;
    }

    int n;
    input >> n; // Размер матрицы смежности

    vector<vector<int>> graph(n, vector<int>(n, 0));

    // Заполнение матрицы смежности
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            input >> graph[i][j];
    input.close();

    // Нахождение сильно связных компонент
    vector<vector<int>> sccList;
    KosarajuSharirSCC(graph, sccList);

    // Запись результата в файл
    ofstream output("output.txt");
    if (!output) {
        cerr << "Unable to open file";
        return 1;
    }

    output << "Number of strongly connected components: " << sccList.size() << endl;
    for (int i = 0; i < sccList.size(); ++i) {
        output << "Component " << i + 1 << ": ";
        for (int j : sccList[i])
            output << j << " ";
        output << endl;
    }
    output.close();

    return 0;
}
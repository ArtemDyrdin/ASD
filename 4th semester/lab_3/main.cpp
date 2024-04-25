#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// Функция для обхода графа в ширину и нахождения компоненты связности
void BFS(vector<vector<int>> &graph, vector<bool> &visited, int start, vector<int> &component) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        component.push_back(current); // Добавляем вершину в текущую компоненту связности

        // Перебираем смежные вершины
        for (int i = 0; i < graph.size(); ++i)
            if (graph[current][i] == 1 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
    }
}

// Функция для нахождения компонент связности в графе
int findConnectedComponents(vector<vector<int>> &graph, vector<vector<int>> &components) {
    int n = static_cast<int>(graph.size());
    vector<bool> visited(n, false);
    int componentCount = 0;

    // Обходим все вершины графа
    for (int i = 0; i < n; ++i)
        if (!visited[i]) {
            vector<int> component;
            BFS(graph, visited, i, component);
            components.push_back(component);
            ++componentCount;
        }

    return componentCount;
}

int main() {
    // Чтение графа из файла
    ifstream input("input.txt");
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

    // Нахождение компонент связности
    vector<vector<int>> components;
    int componentCount = findConnectedComponents(graph, components);

    // Запись результата в файл
    ofstream output("output.txt");
    if (!output) {
        cerr << "Unable to open file";
        return 1;
    }

    output << "Number of connected components: " << componentCount << endl;
    for (int i = 0; i < componentCount; ++i) {
        output << "Component " << i + 1 << ": ";
        for (int j: components[i])
            output << j << " ";
        output << endl;
    }
    output.close();

    return 0;
}
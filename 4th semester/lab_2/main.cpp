#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// чтение матрицы смежности из файла
vector<vector<int>> readAdjacencyMatrix(const string& filePath) {
    ifstream file(filePath);
    vector<vector<int>> adjacencyMatrix;
    if (file.is_open()) {
        int numVertices;
        file >> numVertices;

        adjacencyMatrix.resize(numVertices, vector<int>(numVertices));

        for (int i = 0; i < numVertices; ++i)
            for (int j = 0; j < numVertices; ++j)
                file >> adjacencyMatrix[i][j];
        file.close();
    }
    else
        cerr << "Unable to open file: " << filePath << endl;
    return adjacencyMatrix;
}

// поиск кратчайших путей из заданной вершины с помощью BFS
vector<int> bfsShortestPaths(const vector<vector<int>>& adjacencyMatrix, int startVertex) {
    int numVertices = static_cast<int>(adjacencyMatrix.size());
    vector<int> distances(numVertices, -1); // Инициализируем все расстояния как -1 (недостижимо)
    queue<int> q;

    q.push(startVertex);
    distances[startVertex] = 0; // Расстояние от стартовой вершины до самой себя равно 0

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < numVertices; ++neighbor)
            if (adjacencyMatrix[currentVertex][neighbor] > 0 && distances[neighbor] == -1) {
                q.push(neighbor);
                distances[neighbor] = distances[currentVertex] + 1;
            }
    }

    return distances;
}

// запись результатов в файл
void writeResultToFile(const vector<int>& distances, const string& outputPath) {
    ofstream file(outputPath);
    if (file.is_open()) {
        file << "Shortest paths from the start vertex:\n";
        for (int i = 0; i < distances.size(); ++i) {
            file << "Vertex: " << i << ", Distance: " << distances[i] << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file: " << outputPath << endl;
    }
}

int main() {
    string filePath = "input.txt"; // Путь к файлу с матрицей смежности
    string outputPath = "shortest_paths.txt"; // Путь к файлу для записи результатов
    int startVertex = 0; // Начальная вершина для поиска кратчайших путей

    // Чтение матрицы смежности из файла
    vector<vector<int>> adjacencyMatrix = readAdjacencyMatrix(filePath);

    // Поиск кратчайших путей из заданной вершины
    vector<int> distances = bfsShortestPaths(adjacencyMatrix, startVertex);

    // Запись результатов в файл
    writeResultToFile(distances, outputPath);

    return 0;
}
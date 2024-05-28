import sys

# Функция для считывания матрицы смежности из файла
def read_adjacency_matrix(filename):
    with open(filename, 'r') as file:
        matrix = []
        for line in file:
            row = list(map(int, line.split()))
            matrix.append(row)
    return matrix

# Преобразование матрицы смежности в список ребер
def adjacency_matrix_to_edges(matrix):
    edges = []
    n = len(matrix)
    for i in range(n):
        for j in range(n):
            if matrix[i][j] != 0 and matrix[i][j] != sys.maxsize:
                edges.append((i, j, matrix[i][j]))
    return edges

# Алгоритм Беллмана-Форда
def bellman_ford(matrix, start_vertex):
    n = len(matrix)
    distances = [sys.maxsize] * n
    distances[start_vertex] = 0
    edges = adjacency_matrix_to_edges(matrix)

    # Перебор всех ребер n-1 раз
    for _ in range(n - 1):
        for u, v, weight in edges:
            if distances[u] != sys.maxsize and distances[u] + weight < distances[v]:
                distances[v] = distances[u] + weight

    # Проверка на наличие отрицательных циклов
    for u, v, weight in edges:
        if distances[u] != sys.maxsize and distances[u] + weight < distances[v]:
            print("Граф содержит отрицательный цикл")
            return None

    return distances

if __name__ == "__main__":
    filename = 'input.txt'
    start_vertex = 0
    matrix = read_adjacency_matrix(filename)

    distances = bellman_ford(matrix, start_vertex)
    if distances is not None:
        print(f"Кратчайшие пути от вершины {start_vertex}: {distances}")

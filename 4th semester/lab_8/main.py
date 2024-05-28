import sys

# Функция для считывания матрицы смежности из файла
def read_adjacency_matrix(filename):
    with open(filename, 'r') as file:
        matrix = []
        for line in file:
            row = list(map(int, line.split()))
            matrix.append(row)
    return matrix

def dijkstra(matrix, start_vertex):
    '''Алгоритм Дейкстры'''
    n = len(matrix)
    distances = [sys.maxsize] * n
    distances[start_vertex] = 0
    visited = [False] * n

    for _ in range(n):
        # Выбираем вершину с минимальным расстоянием, которая еще не посещена
        min_distance = sys.maxsize
        min_vertex = -1
        for vertex in range(n):
            if not visited[vertex] and distances[vertex] < min_distance:
                min_distance = distances[vertex]
                min_vertex = vertex

        # Если все вершины посещены, то прерываем цикл
        if min_vertex == -1:
            break

        # Помечаем выбранную вершину как посещенную
        visited[min_vertex] = True

        # Обновляем расстояния до соседей выбранной вершины
        for neighbor in range(n):
            if matrix[min_vertex][neighbor] > 0 and not visited[neighbor]:
                new_distance = distances[min_vertex] + matrix[min_vertex][neighbor]
                if new_distance < distances[neighbor]:
                    distances[neighbor] = new_distance

    return distances

# Пример использования
if __name__ == "__main__":
    filename = 'input.txt'
    start_vertex = 0
    matrix = read_adjacency_matrix(filename)
    distances = dijkstra(matrix, start_vertex)
    print(f"Кратчайшие пути от вершины {start_vertex}: {distances}")

def read_adjacency_matrix(filename):
    with open(filename, 'r') as file:
        matrix = []
        for line in file:
            row = list(map(int, line.split()))
            matrix.append(row)
    return matrix

def is_connected(matrix):
    n = len(matrix)
    visited = [False] * n

    def dfs(v):
        visited[v] = True
        for u in range(n):
            if matrix[v][u] > 0 and not visited[u]:
                dfs(u)

    # Найти первую вершину с непустым списком смежности
    start_vertex = next((i for i in range(n) if any(matrix[i])), None)
    if start_vertex is None:
        return True  # Пустой граф считается связным

    dfs(start_vertex)
    
    # Проверить, что все вершины с непустым списком смежности посещены
    return all(visited[i] or not any(matrix[i]) for i in range(n))

def has_eulerian_cycle(matrix):
    # Все вершины должны иметь четную степень
    return all(sum(row) % 2 == 0 for row in matrix)

def remove_edge(matrix, u, v):
    matrix[u][v] -= 1
    matrix[v][u] -= 1

def find_eulerian_cycle(matrix):
    n = len(matrix)
    stack = []
    cycle = []

    # Найти первую вершину с непустым списком смежности
    start_vertex = next(i for i in range(n) if any(matrix[i]))
    stack.append(start_vertex)

    while stack:
        v = stack[-1]
        has_neighbors = False
        for u in range(n):
            if matrix[v][u] > 0:
                stack.append(u)
                remove_edge(matrix, v, u)
                has_neighbors = True
                break
        if not has_neighbors:
            cycle.append(stack.pop())

    return cycle

if __name__ == "__main__":
    filename = 'input.txt'
    matrix = read_adjacency_matrix(filename)

    if not is_connected(matrix):
        print("Граф не является связным.")
    elif not has_eulerian_cycle(matrix):
        print("Граф не имеет эйлерова цикла, так как не все вершины имеют четную степень.")
    else:
        cycle = find_eulerian_cycle(matrix)
        print("Эйлеров цикл:", cycle)

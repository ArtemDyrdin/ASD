def knapsack(W, wt, val, n):
    """
    Функция для решения задачи о рюкзаке (раскладке по ящикам)
    W - максимальный вес рюкзака
    wt - список весов предметов
    val - список стоимостей предметов
    n - количество предметов
    """
    # Инициализируем таблицу для хранения промежуточных результатов
    # K[i][w] — это максимальная стоимость, которая может 
    # быть достигнута с первыми i предметами и максимальным весом w
    K = [[0 for x in range(W + 1)] for x in range(n + 1)]

    # Построение таблицы K[][]
    for i in range(n + 1):
        for w in range(W + 1):
            if i == 0 or w == 0:
                K[i][w] = 0
            elif wt[i - 1] <= w:
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w])
            else:
                K[i][w] = K[i - 1][w]

    # Максимальная стоимость, которая может быть достигнута с данным весом W
    return K[n][W]

if __name__ == "__main__":
    val = [60, 100, 120]  # Стоимости предметов
    wt = [10, 20, 30]     # Веса предметов
    W = 50                # Максимальный вес рюкзака
    n = len(val)
    max_value = knapsack(W, wt, val, n)
    print(f"Максимальная стоимость, которая может быть достигнута: {max_value}")
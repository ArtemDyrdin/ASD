def subset_sum_greedy(numbers, target):
    """
    Жадный алгоритм для задачи о суммах подмножеств.
    
    numbers - список чисел
    target - целевая сумма
    
    Возвращает подмножество чисел, сумма которых равна целевой сумме (если существует).
    """
    # Сортируем числа в порядке возрастания
    numbers.sort(reverse=True)
    
    current_sum = 0
    subset = []
    
    for number in numbers:
        if current_sum + number <= target:
            subset.append(number)
            current_sum += number
        if current_sum == target:
            return subset
    
    return None  # Если подмножество не найдено

# Основной код
if __name__ == "__main__":
    numbers = [1,2,3, 4,5]
    target = 10
    result = subset_sum_greedy(numbers, target)
    
    if result is not None:
        print(f"Найдено подмножество с суммой {target}: {result}")
    else:
        print(f"Подмножество с суммой {target} не найдено")

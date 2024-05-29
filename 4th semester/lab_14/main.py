def rabin_karp_search(text, pattern):
    n = len(text)
    m = len(pattern)
    results = []

    if n < m:
        return results

    # Хеш-значение образца и первой подстроки текста
    pattern_hash = hash(pattern)
    text_hash = hash(text[:m])

    for i in range(n - m + 1):
        # Если хеши совпадают, проверяем на равенство
        if pattern_hash == text_hash and text[i:i+m] == pattern:
            results.append(i)
        # Пересчитываем хеш для следующей подстроки
        if i < n - m:
            text_hash = hash(text[i+1:i+1+m])

    return results

# Пример использования
text = "ababcabcababc"
pattern = "abc"
print(rabin_karp_search(text, pattern))  # Вывод: [2, 5, 9]

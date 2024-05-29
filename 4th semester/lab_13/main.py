def bad_character_table(pattern):
    bad_char = {}
    m = len(pattern)
    for i in range(m - 1):
        bad_char[pattern[i]] = i
    return bad_char

def good_suffix_table(pattern):
    m = len(pattern)
    good_suffix = [0] * (m + 1)
    border_pos = [0] * (m + 1)

    i = m
    j = m + 1
    border_pos[i] = j

    while i > 0:
        while j <= m and pattern[i - 1] != pattern[j - 1]:
            if good_suffix[j] == 0:
                good_suffix[j] = j - i
            j = border_pos[j]
        i -= 1
        j -= 1
        border_pos[i] = j

    j = border_pos[0]
    for i in range(m + 1):
        if good_suffix[i] == 0:
            good_suffix[i] = j
        if i == j:
            j = border_pos[j]

    return good_suffix

def boyer_moore_search(text, pattern):
    n = len(text)
    m = len(pattern)
    if m == 0:
        return []

    bad_char = bad_character_table(pattern)
    good_suffix = good_suffix_table(pattern)

    s = 0
    results = []

    while s <= n - m:
        j = m - 1
        while j >= 0 and pattern[j] == text[s + j]:
            j -= 1
        if j < 0:
            results.append(s)
            s += good_suffix[0]
        else:
            bad_char_shift = j - bad_char.get(text[s + j], -1)
            good_suffix_shift = good_suffix[j + 1]
            s += max(bad_char_shift, good_suffix_shift)

    return results

# Пример использования
text = "ababcabcababc"
pattern = "abc"
print(boyer_moore_search(text, pattern))  # Вывод: [2, 5, 9]

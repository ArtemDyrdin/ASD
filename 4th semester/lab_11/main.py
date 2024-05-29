def build_transition_function(pattern):
    m = len(pattern)
    alphabet = set(pattern)
    delta = {}

    for q in range(m + 1):
        for a in alphabet:
            k = min(m, q + 1)
            while k > 0 and pattern[:k] != (pattern[:q] + a)[-k:]:
                k -= 1
            delta[(q, a)] = k
    return delta

def finite_automaton_matcher(text, pattern):
    delta = build_transition_function(pattern)
    n = len(text)
    m = len(pattern)
    q = 0
    results = []

    for i in range(n):
        q = delta.get((q, text[i]), 0)
        if q == m:
            results.append(i - m + 1)
    
    return results

# Пример использования
text = "ababcabcababc"
pattern = "abc"
print(finite_automaton_matcher(text, pattern))  # Вывод: [2, 5, 10]

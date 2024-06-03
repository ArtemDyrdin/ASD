def compute_lps_array(s):
    n = len(s) # длина строки s
    lps = [0] * n # создаем массив lps длиной n, заполненный нулями
    length = 0 # длина предыдущего наибольшего префикс-суффикса
    i = 1 # индекс, который мы будем использовать для обхода строки

    # основной цикл для построения массива lps
    while i < n:
        if s[i] == s[length]:
            length += 1
            lps[i] = length 
            i += 1
        else:
            if length != 0:
                length = lps[length - 1]
            else:
                lps[i] = 0
                i += 1
    
    return lps

def find_period(s):
    # Вычисляем массив lps для строки s
    lps = compute_lps_array(s)
    length = len(s) # длина строки s
    period = length - lps[-1] # определяем предполагаемый период как длина строки минус последний элемент lps

    # Проверяем, является ли строка периодической
    if length % period == 0: # если длина строки делится на период без остатка
        return s[:period] # возвращаем подстроку от начала до периода
    else:
        return s # в противном случае возвращаем всю строку

s = "ababab"
period = find_period(s)
print(f"Период строки '{s}': '{period}'")

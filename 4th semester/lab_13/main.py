NO_OF_CHARS = 256
 
def badCharHeuristic(string, size):
    ''' Функция эвристики плохого символа '''
    # Инициализируем все вхождения как -1
    badChar = [-1] * NO_OF_CHARS
 
    # Заполняем фактическое значение последнего вхождения
    for i in range(size):
        badChar[ord(string[i])] = i
 
    # возвращаем инициализированный список
    return badChar
 
def search(txt, pat):
    ''' Функция поиска шаблона через эвристику плохого символа алгоритма Бойера-Мура '''
    m = len(pat)
    n = len(txt)
 
    badChar = badCharHeuristic(pat, m) # список плохих символов
 
    s = 0 # сдвиг шаблона относительно текста

    while s <= n - m:
        j = m - 1
 
        # пока символы шаблона и текста совпадают при данном сдвиге s
        while j >= 0 and pat[j] == txt[s + j]:
            j -= 1
 
        # Если шаблон присутствует при текущем сдвиге, то индекс j станет -1 после вышеуказанного цикла
        if j < 0:
            print("Шаблон найден при сдвиге = {}".format(s))
 
            # Сдвигаем шаблон так, чтобы следующий символ в тексте совпал с последним 
            # вхождением этого символа в шаблоне
            s += (m - badChar[ord(txt[s + m])] if s + m < n else 1)
        else:
            # Сдвигаем шаблон так, чтобы плохой символ в тексте
            # совпал с последним вхождением этого символа в шаблоне.
            s += max(1, j - badChar[ord(txt[s + j])]) # max - чтобы гарантировать положиьельный сдвиг
 
if __name__ == '__main__':
    txt = "ABAAABCD"
    pat = "ABC"
    search(txt, pat)

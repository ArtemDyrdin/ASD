n = int(input('Введите количество строк: '))

strs = []
for i in range(n):
    string = input(f'строка {i+1}: ')
    strs.append(string)

def findWinner(strs):

    # исход при только четных строках или только нечетных
    odd_strs = []
    even_strs = []
    for i in strs:
        if len(i)%2 == 1:
            odd_strs.append(i)
        elif len(i)%2 == 0:
            even_strs.append(i)

    if len(even_strs) == 0:
        print('При любой стратегии выигрывает 2-й игрок')
        return
    if len(odd_strs) == 0:
        print('При любой стратегии выигрывает 1-й игрок')
        return
    
    for odd_str in odd_strs:
        current_str = odd_str[0]
        current_letter = 0
        while True:
            for even_str in even_strs:
                if even_str[:current_letter+1] == current_str:
                    for odd_str in odd_strs:
                        if odd_str[:current_letter+1] == current_str:
                            print('huinya')

findWinner(strs)

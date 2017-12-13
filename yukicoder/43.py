import itertools

n = int(input())
s = [list(input()) for i in range(n)]

ret = n
undefined = []
for i in range(n):
    for j in range(i + 1, n):
        if s[i][j] == '-':
            undefined.append((i, j))
for d in itertools.product('ox', repeat = len(undefined)):
    win = [0] * n
    for i in range(n):
        for j in range(i + 1, n):
            if s[i][j] == 'o':
                win[i] += 1
            elif s[i][j] == 'x':
                win[j] += 1
            elif s[i][j] == '-':
                if d[undefined.index((i,j))] == 'o':
                    win[i] += 1
                else:
                    win[j] += 1
    ret = min(ret, sorted(list(set(win)))[::-1].index(win[0]) + 1)
print(ret)

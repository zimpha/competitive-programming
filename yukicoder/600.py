s = 'abcdefghijklmnopqrstuvwxyz'
def gen(level, n):
    if n == 1:
        return s[level % 26]
    elif n == 2:
        return s[level % 26] + s[level % 26]
    elif n % 2 == 0:
        u = s[level % 26] * 2
        return u + gen(level + 1, n // 2 - 1) + u
    else:
        return s[level % 26] + gen(level + 1, n - 1) + s[level % 26]

print(gen(0, int(input())))

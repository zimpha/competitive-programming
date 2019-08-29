def catalan(n, k, bound):
    assert n >= 1 and k >= 1
    if k > n:
        return 0
    ret = 1
    for i in range(n, 2 * n - k):
        ret = ret * (i + 1) // (i + 1 - n)
        if ret * k > bound * (n * 2 - k):
           return bound + 1
    return ret * k // (n * 2 - k)

n, k = map(int, input().split())
s = []
c = 0
for i in range(n * 2):
    if c + 1 <= n:
        x = n * 2 - i - 1
        y = c + 1
        if x % 2 != y % 2:
            ways = 0
        else:
            ways = catalan((x + y) // 2 + 1, y + 1, k)
        if ways >= k:
            c += 1
            s.append('(')
            continue
        else:
            k -= ways
    s.append(')')
    c -= 1
print(''.join(s))

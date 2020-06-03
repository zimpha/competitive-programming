def gao(n):
    l, r = 0, n
    while l < r:
        m = (l + r + 1) // 2
        if m * (m + 1) // 2 <= n:
            l = m
        else:
            r = m - 1
    return l

def solve(L, R, x):
    if L < x or R < x + 1:
        return L, R, x - 1
    left, right = 0, 10 ** 18
    while left < right:
        m = (left + right + 1) // 2
        if L >= (m + x) * (m + 1) and R >= (m + 1 + x) * (m + 1):
            left = m
        else:
            right = m - 1
    L -= (left + x) * (left + 1)
    R -= (left + 1 + x) * (left + 1)
    return L, R, x + left * 2 + 1

T = int(input())
for cas in range(1, T + 1):
    L, R = map(int, input().split())
    delta = abs(L - R)
    step = gao(delta)
    if L >= R:
        L -= step * (step + 1) // 2
    else:
        R -= step * (step + 1) // 2
    if L >= R:
        L, R, step = solve(L, R, step + 1)
    else:
        R, L, step = solve(R, L, step + 1)
    for __ in range(10):
        if L >= R:
            if L >= step + 1:
                L -= step + 1
                step += 1
            else:
                break
        else:
            if R >= step + 1:
                R -= step + 1
                step += 1
            else:
                break
    print("Case #{}: {} {} {}".format(cas, step, L, R));

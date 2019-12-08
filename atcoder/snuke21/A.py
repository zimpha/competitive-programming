n = int(input())
l, r = 1, n
while l < r:
    m = (l + r) >> 1
    if m * (m + 1) // 2 >= n:
        r = m
    else:
        l = m + 1
if r * (r + 1) // 2 == n:
    print(r)
else:
    print(-1)

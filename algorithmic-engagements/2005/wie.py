n = int(input())
p = []
for i in range(n + 1):
    p.append(int(input()))
r, b = 0, 1
for i in range(n + 1):
    t = b * p[i]
    if (n - i) % 2 == 0:
        r += t
    else:
        r -= t
    b = b * (n + 1 - i) // (i + 1)
print(r)

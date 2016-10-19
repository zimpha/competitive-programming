def solve(n):
    ret = 1
    i = 2
    while i * i <= n:
        cnt = 0
        while n % i == 0:
            cnt += 1
            n /= i
        ret *= 2 * cnt + 1
        i += 1
    if n > 1:
        ret *= 3
    return (ret + 1) / 2

n = 1
while True:
    r = solve(n)
    if r > 1000:
        break
    n += 1
    if n % 100000 == 0:
        print n
print n

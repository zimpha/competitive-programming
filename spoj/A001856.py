def prepare():
    a = [1, 2]
    s = set()
    s.add(0)
    s.add(1)
    v = 0
    for n in range(3, 800):
        if n % 2 == 0:
            while v in s:
                v += 1
            a.append(v + a[-1])
        else:
            a.append(a[-1] * 2)
        for i in range(n - 1):
            s.add(a[-1] - a[i])
    fail = [0]
    for i in range(1, len(a)):
        if i % 2 == 1:
            for j in range(0, i - 1):
                fail.append(a[i] - a[j])
        else:
            for j in range(i):
                fail.append(a[i] - a[j])
    fail.sort()
    return fail

def nth(n, fail):
    total = 1
    now = 1
    m = len(fail)
    for i in range(1, m):
        v = fail[i] - fail[i - 1] - 1
        if total + v * 2 >= n:
            delta = n - total
            v = delta // 2
            now *= 2 ** v
            for j in range(v):
                now += 2 ** (j + 1) * (v - j + fail[i - 1])
            if delta % 2 == 1:
                now += fail[i - 1] + v + 1
            break
        now *= 2 ** v
        for j in range(v):
            now += 2 ** (j + 1) * (v - j + fail[i - 1])
        total += v * 2

mod = 10 ** 9 + 7
fail = prepare()
T = int(input())
query = []
for i in range(T):
    query.append((int(input()), i))
query.sort()
answer = [0] * T

def calc(v, s, n):
    t = pow(2, n % (mod - 1) + mod - 1, mod)
    n %= mod
    a = (v * t + 2 * (t - 1 - n - s + t * s)) % mod
    b = ((t - 1) * (v * 2 + 4) - n * (n + 3) + s * 2 * (t * 2 - 2 - n)) % mod
    b = b * 500000005 % mod
    return a, b

total = 1
value = 1
now = 1
j = 0
for i in range(1, len(fail)):
    n = fail[i] - fail[i - 1] - 1
    s = fail[i - 1] % mod + 1
    next = total + n * 2
    while j < T and next >= query[j][0]:
        delta = query[j][0] - total
        a, b = calc(value, s, delta // 2)
        if delta % 2:
            b = (b + a + s + delta // 2) % mod
        answer[query[j][1]] = (now + b) % mod
        j += 1
    if j == T:
        break
    tmp = calc(value, s, n)
    value = tmp[0]
    now = (now + tmp[1]) % mod
    total = next

for x in answer:
    if x < 0:
        x += mod
    print(x)

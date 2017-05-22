def brute(b):
    d = {}
    for i in xrange(len(b)):
        d[i] = b[i]
    step = 0
    while max(d.values()) > 1:
        for i in d:
            if d[i] < 2: continue
            d[i] -= 2
            if i + 1 in d: d[i + 1] += 1
            else: d[i + 1] = 1
            if i - 1 in d: d[i - 1] += 1
            else: d[i - 1] = 1
            break
        step += 1
    l = []
    for i in d:
        if d[i] > 0:
            l.append(i)
    l.sort()
    return step, l, len(l), l[-1] - l[0] + 1

def calc(n):
    return n * (n + 1) * (2 * n + 1) / 6

def run(bow):
    if len(bow) == 1:
        return calc(bow[0] / 2)
    s0, s1, s2 = sum(bow), 0, 0
    for i in xrange(len(bow)):
        s1 += bow[i] * (i + s0)
        s2 += bow[i] * (i + s0) ** 2
    for i in xrange(s0):
        remove = s0 * (s0 + 1 + i + i) / 2 - s1
        if remove >= 0 and remove < s0:
            st, ed = i, i + s0
            break
    total = 0
    for i in xrange(st, ed + 1):
        total += i ** 2
    total -= (st + remove) ** 2
    return (total - s2) / 2

t = [123456]
b = []
for i in xrange(1500):
    if t[-1] % 2 == 0:
        t.append(t[-1] / 2)
    else:
        t.append((t[-1] / 2) ^ 926252)
    b.append(t[-1] % (2 ** 11) + 1)
print run(b)
print run([289, 145])

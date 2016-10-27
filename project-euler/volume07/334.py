def run(n, m):
    d = {}
    d[0] = n
    d[1] = m
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
    return step

for i in xrange(1, 10):
    for j in xrange(1, 10):
        print run(i, j),
    print ''

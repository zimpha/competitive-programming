#http://www.jstor.org/stable/2690263?seq=8#page_scan_tab_contents
def g(n, d):
    r = n + d - 2 + (6 * n + 2) * (n - d)
    i = d
    while i < n:
        j = min(n - 1, n / (n / i))
        r += 2 * (n / i) * (j - i + 1)
        i = j + 1
    return r

mark = [0] * (10 ** 6)
d = [1] * (10 ** 6)
pl = []
for i in xrange(2, 10 ** 6):
    for j in xrange(i * 2, 10 ** 6, i):
        d[j] = i
    if mark[i]:
        continue
    pl.append(i)
    for j in xrange(i * 2, 10 ** 6, i):
        mark[j] = 1
ret = 0
for i in xrange(1, pl[10000]):
    ret += g(i + 1, d[i + 1])
print ret

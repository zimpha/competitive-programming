def count(s, t, n, mod):
    if len(s) + len(t) <= n:
        return pow(26, n - len(s) - len(t), mod)
    else:
        e = len(s) + len(t) - n
        if e <= len(s) and e <= len(t) and s[-e:] == t[:e]:
            return 1
        else:
            return 0

for it in xrange(int(raw_input())):
    L, m = map(int, raw_input().split())
    s = raw_input().strip()
    t = raw_input().strip()
    ret = count(s, t, L, m) + count(t, s, L, m)
    if len(s) > len(t) and s.startswith(t) and s.endswith(t):
        ret -= count(s, s, L, m)
    elif t.startswith(s) and t.endswith(s):
        ret -= count(t, t, L, m)
    print (ret % m + m) % m

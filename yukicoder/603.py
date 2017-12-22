mod = 10 ** 6 + 3
denom = 10 ** 40
fac = [1] * mod
inv = [1] * mod

for i in xrange(2, mod):
    fac[i] = i * fac[i - 1] % mod
    inv[i] = (mod - mod / i) * inv[mod % i] % mod

def solve():
    def binom(n, m):
        if n < m: return 0
        if n == m or m == 0: return 1
        nq, nr = divmod(n, mod)
        mq, mr = divmod(m, mod)
        if nr < mr: return 0
        return fac[nr] * inv[fac[mr]] * inv[fac[nr - mr]] * binom(nq, mq) % mod

    counts = map(int, raw_input().split())
    s = raw_input()
    n = len(s)
    lens = []
    for i in xrange(26):
        lens.append({})
    freqs = [0] * 26
    last, cnt = -1, 0
    for c in s:
        i = ord(c) - ord('a')
        if last == i:
            cnt += 1
        else:
            if cnt:
                if cnt in lens[last]:
                    lens[last][cnt] += 1
                else:
                    lens[last][cnt] = 1
            cnt = 1
        freqs[i] += 1
        last = i
    if cnt in lens[last]:
        lens[last][cnt] += 1
    else:
        lens[last][cnt] = 1
    lens = [x.items() for x in lens]
    ans = 1
    for i in xrange(26):
        if counts[i] < freqs[i]:
            return 0
        if freqs[i] == 0 or counts[i] == freqs[i]:
            continue
        if len(lens[i]) == 1 and lens[i][0][1] == 1:
            ans = ans * binom(counts[i], lens[i][0][0]) % mod
        else:
            rest = counts[i] - freqs[i]
            ok = denom + 1
            ng = n * denom + 1
            exact = False
            while ng - ok > 1:
                mid = (ok + ng) >> 1
                total = 0
                for l, c in lens[i]:
                    total += (l * denom) / (mid - denom) * c
                if total >= rest:
                    ok = mid
                    if total == rest:
                        exact = True
                        ng = mid
                else:
                    ng = mid
            for l, c in lens[i]:
                k = (l * denom) / (ng - denom)
                if k:
                    ans = ans * pow(binom(l + k, l) % mod, c, mod) % mod
                    rest -= k * c
            assert rest >= 0
            if not exact:
                for l, c in lens[i]:
                    k1 = (l * denom) / (ok - denom)
                    k2 = (l * denom) / (ng - denom)
                    if k1 > k2:
                        assert k1 == k2 + 1
                        ans = ans * pow((k1 + l) * inv[k1 % mod] % mod, min(rest, c), mod) % mod
                        rest -= min(rest, c)
                        if rest == 0:
                            break
    return ans

print solve()

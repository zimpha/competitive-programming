p = [2L, 3L, 5L, 7L, 11L, 13L, 17L, 19L, 23L, 29L, 31L, 37L, 41L, 43L, 47L]
ret, upp = 0, 10 ** 15 - 2

def search(d, now):
    global ret
    if now > ret:
        print now
        ret = now
    if d < 0: return
    while now <= upp:
        search(d - 1, now)
        now *= p[d]

search(len(p) - 1, 1)
print ret

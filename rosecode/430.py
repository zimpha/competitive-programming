from fractions import *

def solve(M, N):
    f = [1, 1]
    for i in xrange(2, N + M):
        f.append(f[i - 1] + f[i - 2])
    f = [1 + x % 5 for x in f]
    tm, tn = sum(f[:M]), sum(f[M:])

    def area(i, j):
        if i < 0 or j < 0:
            return 0
        if i == M - 1:
            return Fraction(sum(f[M : M + j + 1]), tn)
        if j == N - 1:
            return Fraction(sum(f[: i + 1]), tm)
        AF = sum(f[:i + 1])
        FB = tm - AF
        BD = tn
        DC = tn - sum(f[M : M + j + 1])
        x = Fraction(AF, FB) * Fraction(BD, DC)
        x = x / (x + 1)
        return Fraction(BD - DC, BD) * Fraction(AF, tm) * x
    ret = []
    for i in xrange(M):
        for j in xrange(N):
            x = area(i, j) - area(i - 1, j) - area(i, j - 1) + area(i - 1, j - 1)
            ret.append(x)
    ret.sort()
    if N * M % 2 == 0:
        median = (ret[N * M / 2] + ret[N * M / 2 - 1]) / 2
    else:
        median = ret[N * M / 2]
    print ret[0], median, ret[-1]
    return (ret[0], median, ret[-1])

print solve(2, 2)
print solve(19, 23)

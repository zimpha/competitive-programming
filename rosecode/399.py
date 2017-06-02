seq = [(1, 1, 1), (2, 3, 4)]
for i in xrange(2, 100):
    c = seq[-1][0] * 2 + seq[-2][0]
    s = seq[-1][1] * 2 + seq[-2][1]
    p = seq[-1][2] * 2 + seq[-2][2] + seq[-1][0] * seq[-1][1] + 2 * seq[-2][0] * seq[-1][1]
    seq.append((c, s, p))

def solve(m, n, p):
    if seq[m][0] == n:
        return seq[m][2] + p * seq[m][0]
    if seq[m - 1][0] >= n:
        return solve(m - 1, n, p)
    if n <= seq[m - 1][0] * 2:
        return solve(m - 1, n - seq[m - 1][0], p + seq[m - 1][1]) + seq[m - 1][2] + p * seq[m - 1][0]
    return solve(m - 2, n - seq[m - 1][0] * 2, p + seq[m - 1][1] * 2) + seq[m - 1][2] + p * seq[m - 1][0] + seq[m - 1][2] + (p + seq[m - 1][1]) * seq[m - 1][0]

def S(n):
    if n == 1: return 1
    return solve(99, n - 1, 0) + n

print S(100)
print S(10 ** 20)

from math import sqrt, ceil, log

#   (\sqrt{p} + \sqrt{q})^{2n} + (\sqrt{p} - \sqrt{q})^{2n}
# = (p + q + 2\sqrt{pq})^n + (p + q - 2\sqrt{pq})^n \in N
# 0 < p + q - 2\sqrt{pq} < 1 => \mathrm{lim}_{n \to \infty}(p + q - 2\sqrt{pq})^n = 0, \mathrm{lim}_{n \to infty} \{(p + q + 2\sqrt{pq})^n\} = 1

def run(n):
    ret = 0
    for p in xrange(1, n + 1):
        for q in xrange(p + 1, n + 1 - p):
            val = p + q - 2 * sqrt(p * q)
            if val <= 0 or val >= 1:
                continue
            ret += int(-ceil(2011 / log(val, 10))) + 1
    return ret

print run(2011)

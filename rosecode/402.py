from math import *
from fractions import *

def isqrt(n):
    x = int(sqrt(n * (1 + 1e-14)))
    while True:
      y = (x + n // x) >> 1
      if y >= x:
          return x
      x = y

def pqa(p0, q0, d, lmm=False):
  sqrt_d = sqrt(d)
  assert 0 < d, "D cannot be negative or zero"
  assert q0 != 0, "Q0 cannot be zero"
  assert (p0 * p0 - d) % q0 == 0, "P0^2 cannot be different from D modulo Q0"
  assert int(sqrt_d) * int(sqrt_d) != d, "D cannot be a perfect square"
  a_i, a_im = 1, 0
  b_i, b_im = 0, 1
  g_i, g_im = q0, -p0
  p_i, q_i = p0, q0
  i, ir = -1, None
  alphas = []
  rs = []
  end = 0
  while True:
    i += 1
    xi_i = (p_i + sqrt_d) / q_i
    xibar_i = (p_i - sqrt_d) / q_i
    alpha_i = int(xi_i)
    a_i, a_im = alpha_i * a_i + a_im, a_i
    b_i, b_im = alpha_i * b_i + b_im, b_i
    g_i, g_im = alpha_i * g_i + g_im, g_i
    # Everything is now as of i
    if ir == None and 1 < xi_i and -1 < xibar_i and xibar_i < 0:
      ir, p_ir, q_ir = i, p_i, q_i
    if ir != None and ir != i and p_i == p_ir and q_i == q_ir:
      end += 1
    if not lmm and end: break
    if lmm and end >= 2: break
    alphas.append(alpha_i)
    # Update p_i and q_i for i+1
    p_i = alpha_i * q_i - p_i
    q_i = (d - p_i * p_i) / q_i
    if lmm and i >= 1 and abs(q_i) == 1:
      rs.append((g_i, b_i))
  if lmm:
    return rs
  else:
    return alphas, i - ir

# Get the minimal solution for x^2 - d.y^2 = epsilon, where epsilon can be 1 or -1
def pell1_min(d, eps):
  assert eps == 1 or eps == -1, "epsilon is different from -1 and 1"
  alphas, l = pqa(0, 1, d)
  if l & 1:
    index = 2 * l - 1 if eps == 1 else l - 1
  else:
    if eps == -1: return None
    index = l - 1
  b_i, b_im = 0, 1
  g_i, g_im = 1, 0
  pl = len(alphas) - l
  for i in xrange(0, index + 1):
    alpha_i = alphas[i] if i < pl else alphas[pl + (i - pl) % l]
    b_i, b_im = alpha_i * b_i + b_im, b_i
    g_i, g_im = alpha_i * g_i + g_im, g_i
  return g_i, b_i

# return all the fundamental solutions for the generalized pell equation: x^2 - d.y^2 = n.
def pell_funds(d, n):
    sd = isqrt(d)
    if sd * sd == d: return []
    sn = isqrt(abs(n))
    tu = pell1_min(d, -1)
    funds = []
    for f in xrange(1, sn + 1):
        if n % (f * f): continue
        m = n / f / f
        l = -(abs(m) / 2) if m % 2 else -(abs(m) / 2) + 1
        for z in xrange(l, abs(m) / 2 + 1):
            if z * z % abs(m) != d % abs(m): continue
            rs = pqa(z, abs(m), d, lmm=True)
            for r, s in rs:
                if r ** 2 - d * s ** 2 == m:
                    funds.append((f * r, f * s))
                elif r ** 2 - d * s ** 2 == -m:
                    if not tu: continue
                    t, u = tu
                    funds.append((f * (r * t + s * u * d), f * (r * u + s * t)))
                else:
                    assert False
    return funds

def gen(n, m, x0, y0):
    assert m * x0 ** 2 - n * y0 ** 2 == 1
    a = x0 ** 2 * m + y0 ** 2 * n
    b = x0 * y0
    x, y = x0, y0
    res = []
    for i in xrange(10):
        if n * y ** 2 > 10 ** 50:
            break
        res.append(n * y ** 2)
        x, y = a * x + b * n * y, a * y + b * m * x
    return res

def is_square(n):
    x = isqrt(n)
    return x * x == n

def solve(n, m):
    # m * (mx)^2 - n * (ny)^2 = 1
    if n == m or is_square(n ** 3) or is_square(m ** 3): return []
    # convert to (m^2x)^2 - nm(ny)^2 = m
    d = n * m
    funds = pell_funds(d, m)
    if not funds: return []
    t, u = pell1_min(d, 1)
    sols = []
    for r, s in funds:
        x, y = r, s
        while True:
            if x % (m * m) == 0 and y % n == 0:
                sols.append(n * y ** 2)
            x, y = x * t + y * u * d, x * u + y * t
            if n * y ** 2 >= 10 ** 40:
                break
    #print n, m, sols
    return sols

N = 2000
mu = [0] * N
for i in xrange(1, N):
    mu[i] += i == 1
    for j in xrange(i + i, N, i):
        mu[j] -= mu[i]

sols = []
for m in xrange(2, 100):
    for n in xrange(2, N):
        if mu[n] and mu[m] and gcd(n, m) == 1:
            sols.extend(solve(n, m))
sols = list(set(sols))
sols.sort()
print sols, sols[10]
# ans = 161722121962021270972777151960327

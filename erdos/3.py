from math import *

def pqa(p0, q0, d):
  sqrt_d = sqrt(d)
  assert 0 < d, "D cannot be negative or zero"
  assert q0 != 0, "Q0 cannot be zero"
  assert (p0*p0 - d) % q0 == 0, "P0^2 cannot be different from D modulo Q0"
  assert int(sqrt_d) * int(sqrt_d) != d, "D cannot be a perfect square"
  a_i, a_im = 1, 0
  b_i, b_im = 0, 1
  g_i, g_im = q0, -p0
  p_i, q_i = p0, q0
  i, ir = -1, None
  alphas = []
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
      break
    alphas.append(alpha_i)
    # Update p_i and q_i for i+1
    p_i = alpha_i * q_i - p_i
    q_i = (d - p_i * p_i) / q_i
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

res = 0
for n in xrange(1, 10 ** 5):
    sq = int(sqrt(n))
    if sq ** 2 == n:
        continue
    x, y = pell1_min(n, 1)
    if x > res:
        print n
        res = x

from copy import deepcopy

def det(m):
  if len(m) == 1:
    return m[0][0]
  elif len(m) == 2:
    return m[0][0] * m[1][1] - m[0][1] * m[1][0]
  else:
    return None

mem = {}
def binom(n, m):
  if n < m or n < 0 or m < 0:
    return 0
  if m == 0 or n == m:
    return 1
  if (n, m) not in mem:
    mem[(n, m)] = binom(n - 1, m) + binom(n - 1, m - 1)
  return mem[(n, m)]

def gen_M(b, x, y, u):
  return [[binom(x[j][u] - x[i][u - 1] + y[j][u] - y[i][u - 1],
                 x[j][u] - x[i][u - 1] + j - i) for j in range(1, b + 1)] for i in range(1, b + 1)]

def gen_P(d, x, y, v):
  return [[binom(x[v][j] - x[v - 1][i] + y[v - 1][i] - y[v][j],
                 x[v][j] - x[v - 1][i] + j - i) for j in range(1, d + 1)] for i in range(1, d + 1)]

def T(a, b, c, d):
  X, x = [], [[0] * (d + 2) for i in range(b + 2)]
  Y, y = [], [[0] * (d + 2) for i in range(b + 2)]
  for k in range(1, b + 1):
    x[k][d + 1] = a
    y[k][d + 1] = c
  for l in range(1, d + 1):
    y[0][l] = c
    x[b + 1][l] = a

  def gen_X(k, l):
    if k == b + 1:
      X.append(deepcopy(x))
      return
    if l == d + 1:
      gen_X(k + 1, 1)
      return
    mx = max(x[k][:l])
    for i in range(1, k):
      mx = max(mx, max(x[i][:l + 1]))
    for v in range(mx, a + 1):
      x[k][l] = v
      gen_X(k, l + 1)
      x[k][l] = 0

  def gen_Y(k, l):
    if k == 0:
      Y.append(deepcopy(y))
      return
    if l == d + 1:
      gen_Y(k - 1, 1)
      return
    mx = max(y[k][:l])
    for i in range(k + 1, b + 1):
      mx = max(mx, max(y[i][:l + 1]))
    for v in range(mx, c + 1):
      y[k][l] = v
      gen_Y(k, l + 1)
      y[k][l] = 0

  gen_X(1, 1)
  gen_Y(b, 1)
  ret = 0
  for x in X:
    for y in Y:
      mul = 1
      for u in range(1, d + 2):
        mul *= det(gen_M(b, x, y, u))
      for v in range(1, b + 2):
        mul *= det(gen_P(d, x, y, v))
      ret += mul
  return ret

print(T(1, 1, 1, 1))
print(T(2, 1, 2, 1))
print(T(3, 2, 3, 2))
print(T(4, 2, 4, 2))
print(T(8, 2, 8, 2))

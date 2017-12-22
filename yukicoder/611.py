mod = 201712111
h, w = list(map(int, input().split()))
g = [input() for i in range(h)]
if h < w:
  g = [[g[i][j] for i in range(h)] for j in range(w)]
  h, w = w, h
else:
  g = [list(g[i]) for i in range(h)]

if g[0][0] == '?': g[0][0] = '1'
if g[-1][-1] == '?': g[-1][-1] = '1'

dp = [[1e9] * w for i in range(h)]
uf = [[0] * w for i in range(h)]
lf = [[0] * w for i in range(h)]
for i in range(h):
  for j in range(w):
    if i: dp[i][j] = min(dp[i][j], dp[i - 1][j])
    if j: dp[i][j] = min(dp[i][j], dp[i][j - 1])
    uf[i][j] = 1 if i and dp[i][j] == dp[i - 1][j] else 0
    lf[i][j] = 1 if j and dp[i][j] == dp[i][j - 1] else 0
    dp[i][j] += int(g[i][j]) if g[i][j] != '?' else 1
    if not i and not j: dp[i][j] = int(g[i][j])
for i in range(h - 1, -1, -1):
  for j in range(w - 1, -1, -1):
    if i == h - 1 and j == w - 1: continue
    valid = 0
    if i + 1 < h: valid |= uf[i + 1][j]
    if j + 1 < w: valid |= lf[i][j + 1]
    uf[i][j] &= valid
    lf[i][j] &= valid
s = 1 << w
u = [0] * s
u[1] = 1
for i in range(1, h * w):
  x, y = divmod(i, w)
  v = [0] * s
  use = (s - 1) ^ (1 << y)
  for mask in range(s):
    u[mask] %= mod
    if not u[mask]: continue
    new_mask = mask & use
    from_left = (y > 0 and lf[x][y] and (mask >> (y - 1) & 1))
    from_up = (uf[x][y] and (mask >> y & 1))
    if g[x][y] == '?':
      if from_left or from_up:
        v[new_mask | (1 << y)] += u[mask]
        v[new_mask] += u[mask] * 8
      else:
        v[new_mask] += u[mask] * 9
    else:
      if from_left or from_up:
        v[new_mask | (1 << y)] += u[mask]
      else:
        v[new_mask] += u[mask]
  u = v

print(dp[-1][-1])
ret = 0
for mask in range(s // 2):
  ret += u[mask | (1 << (w - 1))]
print(ret % mod)

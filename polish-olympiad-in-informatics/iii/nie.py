n = int(input())
k = [int(input()) for i in range(n)]
f = [[-1] * 8 for i in range(8)]
g = [[0] * 8 for i in range(8)]
f[0][0], g[0][0] = 0, 1
cnt = [0] * 8
for i in range(8):
  cnt[i] = cnt[i >> 1] + i % 2
for i in range(n):
  ff = [[-1] * 8 for _ in range(8)]
  gg = [[0] * 8 for _ in range(8)]
  for x in range(8):
    for y in range(8):
      if f[x][y] == -1: continue
      for z in range(8):
        if k[i] and (z >> (k[i] - 1) & 1): continue
        if (x >> 1) & z or (x << 1) & z: continue
        if (y >> 2) & z or (y << 2) & z: continue
        if f[x][y] + cnt[z] > ff[y][z]:
           ff[y][z] = f[x][y] + cnt[z]
           gg[y][z] = g[x][y]
        elif f[x][y] + cnt[z] == ff[y][z]:
           gg[y][z] += g[x][y]
  f, g = ff, gg
mx = 0
for x in range(8):
  for y in range(8):
    mx = max(mx, f[x][y])
cnt = 0
for i in range(8):
  for j in range(8):
    if f[i][j] == mx:
      cnt += g[i][j]
print("{} {}".format(mx, cnt))

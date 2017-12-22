h, w, n = map(int, input().split())
s = [input() for i in range(h)]
cnt = [0] * w
for i in range(h):
  for j in range(w):
    cnt[j] += s[i][j] == '#'
ret = [[0] * 3 for i in range(n)]
empty = [True] * n
cell = [[] for i in range(w)]
for i in range(n):
  c = int(input())
  cell[c].append(i)
for i in range(w):
  cells = []
  if i >= 2: cells.extend([(x, 2) for x in cell[i - 2]])
  if i >= 1: cells.extend([(x, 1) for x in cell[i - 1]])
  cells.extend([(x, 0) for x in cell[i]])
  for x, y in cells:
    if not cnt[i]: break
    if empty[x]:
      ret[x][y] += 1
      cnt[i] -= 1
      empty[x] = False
  for x, y in cells:
    r = min(cnt[i], 3 - ret[x][y])
    ret[x][y] += r
    cnt[i] -= r
for e in ret:
  r = [['.'] * 3 for i in range(3)]
  for i in range(3):
    for j in range(e[i]):
      r[j][i] = '#'
  for i in range(3):
    r[i] = ''.join(r[i])
  print(*r, sep='\n')

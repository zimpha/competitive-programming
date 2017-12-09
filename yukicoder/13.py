def solve(h, w, cells, mapping):
  for i, c in enumerate(cells):
    mapping[c[0]][c[1]] = i
  n = len(cells)
  dsu = [i for i in range(n)]

  def root(x):
    if x != dsu[x]:
      dsu[x] = root(dsu[x])
    return dsu[x]

  dx = [0, 1]
  dy = [1, 0]
  for c in cells:
    for i in range(2):
      x, y = c[0] + dx[i], c[1] + dy[i]
      if x < 0 or x >= h or y < 0 or y >= w or mapping[x][y] == -1:
        continue
      u = root(mapping[c[0]][c[1]])
      v = root(mapping[x][y])
      if u != v:
        dsu[u] = v
      else:
        return True
  for i, c in enumerate(cells):
    mapping[c[0]][c[1]] = -1
  return False

w, h = list(map(int, input().split()))
cells = [[] for i in range(1000)]
mapping = [None] * h
for i in range(h):
  a = list(map(int, input().split()))
  mapping[i] = [-1] * w
  for j in range(w):
    cells[a[j] - 1].append((i, j))

flag = False
for e in cells:
  if solve(h, w, e, mapping):
    flag = True
    break
print('possible' if flag else 'impossible')

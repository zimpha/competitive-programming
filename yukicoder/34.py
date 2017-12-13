from collections import deque

def solve():
  n, v, sy, sx, gy, gx = list(map(int, input().split()))
  if v > (abs(sx - gx) + abs(sy - gy)) * 9:
    return abs(sx - gx) + abs(sy - gy)
  gx, gy = gx - 1, gy - 1
  g = [list(map(int, input().split())) for i in range(n)]
  dis = [[[-1] * (v + 1) for j in range(n)] for i in range(n)]
  dis[sx - 1][sy - 1][v] = 0
  queue = deque()
  queue.append((sx - 1, sy - 1, v))
  dxy = [(0, 1), (0, -1), (1, 0), (-1, 0)]
  while queue:
    u = queue.popleft()
    cost = dis[u[0]][u[1]][u[2]] + 1
    for d in dxy:
      x, y = u[0] + d[0], u[1] + d[1]
      if x < 0 or x >= n or y < 0 or y >= n:
        continue
      z = u[2] - g[x][y]
      if z > 0 and dis[x][y][z] == -1:
        dis[x][y][z] = cost
        if x == gx and y == gy:
          return dis[x][y][z]
        queue.append((x, y, z))
  return -1

print(solve())

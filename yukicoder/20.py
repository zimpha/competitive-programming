from queue import Queue

n, v, oy, ox = list(map(int, input().split()))
a = [list(map(int, input().split())) for i in range(n)]

def get_dist(sx, sy):
  if sx < 0:
    return None
  q = Queue()
  q.put((sx, sy))
  dist = [[1e9] * n for i in range(n)]
  mark = [[0] * n for i in range(n)]
  dist[sx][sy] = 0
  mark[sx][sy] = 1
  dx = [0, 0, 1, -1]
  dy = [1, -1, 0, 0]
  while not q.empty():
    x, y = q.get()
    mark[x][y] = 0
    for i in range(4):
      xx, yy = x + dx[i], y + dy[i]
      if xx < 0 or xx >= n or yy < 0 or yy >= n:
        continue
      cost = dist[x][y] + a[xx][yy]
      if dist[xx][yy] > cost:
        dist[xx][yy] = cost
        if not mark[xx][yy]:
          mark[xx][yy] = 1
          q.put((xx, yy))
  return dist

oy -= 1
ox -= 1
d1 = get_dist(0, 0)
d2 = get_dist(ox, oy)
if d1[n - 1][n - 1] < v:
  print("YES")
elif d2 and d1[ox][oy] < v:
  v = (v - d1[ox][oy]) * 2
  if d2[n - 1][n - 1] < v:
    print("YES")
  else:
    print("NO")
else:
  print("NO")

n = int(input())
p = [0] * n
s = [0] * n

edges = [[] for i in range(n)]
for i in range(n):
  p[i], s[i] = list(map(int, input().split()))
  s[i] -= 1
  edges[s[i]].append(i)

ret = sum(p) / 2
mark = [0] * n
for i in range(n):
  if mark[i]: continue
  queue = []
  x = i
  while not mark[x]:
    mark[x] = 1
    queue.append(x)
    x = s[x]
  mx = 1e9
  while mark[x]:
    mark[x] = 0
    mx = min(mx, p[x])
    x = s[x]
  ret += mx / 2
  for x in queue:
    mark[x] = 1
  while len(queue):
    u = queue[0]
    queue.pop(0)
    for v in edges[u]:
      if not mark[v]:
        mark[v] = 1
        queue.append(v)
print('%.1f' % ret)

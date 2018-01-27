from copy import deepcopy

src = list(map(int, '6 4 3 18 24 29 9 19 25 27 11 15 28 10 16 26 30 22 23 17 2 13 8 14 21 20 12 1 7 5'.split()))
tar = list(map(int, '8 10 18 14 11 17 23 24 30 27 1 9 3 26 29 25 7 20 22 16 5 6 13 12 4 21 2 15 19 28'.split()))
n = 30
step = 40

def add(mem, key, value):
  if key in mem:
    mem[key] += value
  else:
    mem[key] = value

pos = [0] * n
for i, p in enumerate(tar):
  pos[p - 1] = i
src = [pos[x - 1] for x in src]
mark = [0] * n
circle = []
for i in range(n):
  if mark[i]:
    continue
  j, cnt = i, 0
  while not mark[j]:
    mark[j] = 1
    j = src[j]
    cnt += 1
  circle.append(cnt)
circle.sort()

f = {}
add(f, tuple(circle), (n * n) ** step)
for it in range(step):
  print('step %d: ' % it)
  g = {}
  for k in f:
    v = f[k]
    add(g, k, v / n)
    m = len(k)
    for i in range(m):
      if k[i] == 1: continue
      for x in range(1, k[i]):
        now = list(k[:i] + k[i + 1:])
        now.extend([x, k[i] - x])
        now.sort()
        add(g, tuple(now), v * k[i] / n / n)
    for i in range(m):
      for j in range(i):
        now = list(k[:j] + k[j+1:i] + k[i+1:])
        now.append(k[i] + k[j])
        now.sort()
        add(g, tuple(now), v * k[i] * k[j] * 2 / n / n)
  f = g

ret = f[tuple([1] * n)]
for i in range(n):
  ret *= i + 1
print(ret * 1000000 / (n * n) ** step)

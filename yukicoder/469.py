import random as rnd

rnd.seed(2333)
n, q = list(map(int, input().split()))
seed = [rnd.randint(0, 2 ** 60) for i in range(n)] + [0]
now = 0
mem = {0 : 0}
for i in range(q):
  c = input()
  if c[0] == '?':
    print(mem[now])
  else:
    _, l, r, k = c.split()
    now += int(k) * (seed[int(l)] - seed[int(r)])
    if not now in mem:
      mem[now] = i + 1

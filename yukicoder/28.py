def factorize(n):
  f = []
  for i in range(2, n + 1):
    if n % i: continue
    cnt = 0
    while n % i == 0:
      n //= i
      cnt += 1
    f.append((i, cnt))
  return f

for _ in range(int(input())):
  seed, n, k, b = list(map(int, input().split()))
  x = [seed]
  for i in range(n):
    x.append(1 + (x[-1] ** 2 + x[-1] * 12345) % 100000009)
  ret = 1e9
  for p, c in factorize(b):
    cnt = [0] * (n + 1)
    for i, u in enumerate(x):
      while u % p == 0:
        cnt[i] += 1;
        u //= p
    cnt.sort()
    ret = min(ret, sum(cnt[:k]) // c)
  print(ret)


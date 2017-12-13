kr, kb = list(map(int, input().split()))
s = input()
ret = 10
for mask in range(1 << 20):
  t = []
  k = 0
  for c in s:
    if c == 'W' or (mask >> k & 1):
      t.append(c)
    if c != 'W': k += 1
  n = len(t)
  flag = True
  for i, c in enumerate(t):
    if c == 'R' and i + kr < n and t[i + kr] == 'R': flag = False
    if c == 'B' and i + kb < n and t[i + kb] == 'B': flag = False
    if not flag: break
  if flag: ret = max(ret, n)
print(ret)

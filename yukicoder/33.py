n, d, t = list(map(int, input().split()))
pos = dict()
for x in map(int, input().split()):
  y = (x % d + d) % d
  if y in pos:
    pos[y].append(x)
  else:
    pos[y] = [x]
ret = 0
for k, v in pos.items():
  seg = []
  for x in v:
    seg.append((x - d * t, x + d * t))
  seg.sort()
  l, r = seg[0]
  for e in seg[1:]:
    if e[0] <= r:
      r = max(r, e[1])
    else:
      ret += (r - l) // d + 1
      l, r = e
  ret += (r - l) // d + 1
print(ret)

cnt, ret = 0, 0
for i in range(int(input())):
  t, s = input().split()
  t = (int(t) * 12) // 1000
  cnt += min(len(s), t)
  if t < len(s):
    ret += len(s) - t
print(cnt, ret)

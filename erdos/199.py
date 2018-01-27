r = 1
for i in range(6):
  r *= 197 - i
r %= 10 ** 9 + 7
r = bin(r)
cnt = 0
for x in r:
  if x == '1':
    cnt += 1
print(cnt)

d = int(input())
a = list(map(int, input().split()))

for i in range(d, 2, -1):
  a[i - 2] += a[i]

d = min(2, d)
for i in range(d, -1, -1):
  d = i
  if a[i]: break
print(d)
for i in range(d + 1):
  if i == 0:
    print(str(a[i]), end='')
  else:
    print(' ' + str(a[i]), end='')
print()

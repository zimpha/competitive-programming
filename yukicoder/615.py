n, k = map(int, input().split())
a = list(map(int, input().split()))
a.sort()
b = [a[i] - a[i - 1] for i in range(1, n)]
b.sort()
b.reverse()
ret = sum(b)
for i in range(k - 1):
  ret -= b[i]
print(ret)

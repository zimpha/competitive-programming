n = list(input())
ret = ''.join(n)
for i in range(len(n)):
  for j in range(i):
    n[i], n[j] = n[j], n[i]
    ret = max(ret, ''.join(n))
    n[i], n[j] = n[j], n[i]
print(ret)

n = int(input())
k = int(input())
a = [int(input()) for i in range(n)]
group = [[] for i in range(k)]
def search(d, m):
  if d == n:
    if m == k:
      avg = [sum(x) / len(x) for x in group]
      return max(avg) - min(avg)
    else:
      return 0
  ret = 0
  for i in range(min(m + 1, k)):
    group[i].append(a[d])
    ret = max(ret, search(d + 1, max(m, i + 1)))
    group[i].pop(-1)
  return ret

print(int(search(0, 0)))

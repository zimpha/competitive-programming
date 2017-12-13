n = int(input())
p = [1, 2, 3]
m = int(input())
for i in range(m):
  x, y = list(map(int, input().split()))
  p[x - 1], p[y - 1] = p[y - 1], p[x - 1]
for i in range(3):
  if p[i] == n:
    print(i + 1)

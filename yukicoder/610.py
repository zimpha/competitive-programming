n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
order = [0] * n
for i, x in enumerate(a):
  order[x - 1] = i
mx = -1
can = []
for x in b:
  if order[x - 1] > mx:
    can.append(x)
  mx = max(mx, order[x - 1])
can.sort()
for x in can:
  print(x)

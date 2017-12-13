n = int(input())
f = [1, 1]
for i in range(2, n + 1):
  f.append(f[-1] + f[-2])
print(f[-1])

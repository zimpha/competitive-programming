s = input()
n = int(input())
m = len(s)

fib = ["b", "a"]
for i in range(2, 11):
  fib.append(fib[-1] + fib[-2])
cnt = [0] * 11
for i in range(11):
  for j in range(len(fib[i])):
    cnt[i] += s == fib[i][j: j + m]
if n <= 11:
  print(cnt[n - 1])
else:
  s89 = fib[8] + fib[9]
  s99 = fib[9] + fib[9]
  c89 = 0
  c99 = 0
  for i in range(len(fib[8])):
    c89 += i + m - 1 >= len(fib[8]) and s == s89[i: i + m]
  for i in range(len(fib[9])):
    c99 += i + m - 1 >= len(fib[9]) and s == s99[i: i + m]
  for i in range(11, n):
    cnt.append(cnt[-1] + cnt[-2])
    if i % 2 == 0:
      cnt[-1] += c99
    else:
      cnt[-1] += c89
  print(cnt[-1])

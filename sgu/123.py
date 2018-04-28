fib = [1] * 41
k = int(input())
for i in range(2, k):
  fib[i] = fib[i - 1] + fib[i - 2]
print(sum(fib[:k]))

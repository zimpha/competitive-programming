n = input()
n = int(input())
result = 0
while n > 0:
  if n % 2 == 1:
    n -= 2 - n % 4
    result += 1
  n //= 2
print(result)

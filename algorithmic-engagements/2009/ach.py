n = int(input())
if n == 1:
    print(1)
elif n % 4 in [0, 1]:
    n //= 4
    x, y = 2, 1
    for i in range(n - 1):
        y *= i + 1
    for i in range(n * 2 - 1):
        x *= i + 1
    print(x // y)
else:
    print(0)

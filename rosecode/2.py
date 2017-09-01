x, y = 1, 1
while sum(map(int, list(str(x)))) <= 100:
    z = x + y
    x, y = z, x
print x

x, y = map(float, input().split())
print(min(x, 1 - y), x - min(x, y))

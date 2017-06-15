n = int(raw_input())
a = [x - 1 - i for i, x in enumerate(map(int, raw_input().split()))]
x, y = max(a), min(a)
print x - y + min(x, -y)

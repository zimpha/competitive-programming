w = int(input())
h = int(input())
n = int(input())

X = set()
Y = set()
for i in range(n):
    x, y = input().split()
    X.add(x)
    Y.add(y)
print(h * len(X) + w * len(Y) - n - len(X) * len(Y))

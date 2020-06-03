n = int(input())
s = sum(map(int, input().split()))
if n == 0:
    print(0)
else:
    print(s / n)

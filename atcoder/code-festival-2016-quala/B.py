n = int(input())
a = list(map(int, input().split()))
ret = 0
for i in range(n):
    ret += a[i] != i + 1 and a[a[i] - 1] == i + 1
print(ret // 2)

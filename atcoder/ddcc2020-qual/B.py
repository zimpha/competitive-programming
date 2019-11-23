n = int(input())
a = list(map(int, input().split()))
s = sum(a)
now = 0
ret = s
for x in a:
    now += x
    ret = min(ret, abs(s - now - now))
print(ret)

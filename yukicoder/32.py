l = int(input())
m = int(input())
n = int(input())
ret = n % 25
m += n // 25
ret += m % 4
l += m // 4
ret += l % 10
print(ret)

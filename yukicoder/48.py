x = int(input())
y = int(input())
l = int(input())
ret = 0
if y < 0:
  ret += 2
elif x != 0:
  ret += 1
ret += (abs(x) + l - 1) // l + (abs(y) + l - 1) // l
print(ret)

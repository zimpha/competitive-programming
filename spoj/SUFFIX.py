def exgcd(a, b):
  if not b:
    return 1, 0, a
  else:
    y, x, g = exgcd(b, a % b)
    return x, y - x * (a // b), g

def crt(n, c, m):
  def mod(x, y):
    x %= y
    if x < 0: x += y
    return x

  ret, lcm = c[0], m[0]
  for i in range(1, n):
    x, y, g = exgcd(lcm, m[i])
    if (c[i] - ret) % g:
      return -1
    tmp = mod((c[i] - ret) // g * x, m[i] // g)
    ret = mod(ret + lcm * tmp, lcm // g * m[i])
    lcm = lcm // g * m[i];
  return mod(ret, lcm);

n = int(input())
c = [0] * n
m = [0] * n
for i in range(n):
  b, s = input().split()
  b = int(b)
  l = len(s)
  c[i] = int(s, b)
  m[i] = b ** l
print(crt(n, c, m))

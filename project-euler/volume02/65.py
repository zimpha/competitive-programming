a = 0
b = 1
for i in xrange(0, 100):
  if i == 99:
    a += b * 2
  else:
    k = 98 - i
    if k % 3 == 1:
      k = k / 3 + 1
      k *= 2
    else:
      k = 1
    a, b = b, k * b + a
print a, b
s = str(a)
ret = 0
for i in xrange(len(s)):
  ret += ord(s[i]) - ord('0');
print ret

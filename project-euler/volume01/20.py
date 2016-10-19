n = input()
s = 1
for i in xrange(n):
  s = s * (i + 1)
print s

s = str(s)
n = len(s)
ret = 0
for i in xrange(n):
  ret += ord(s[i]) - ord('0');
print ret

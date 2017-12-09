s = input()
t = [''] * len(s)
for i, x in enumerate(s):
  t[i] = chr(ord('A') + ((ord(x) - ord('A') - i - 1) % 26 + 26) % 26)
print(''.join(t))

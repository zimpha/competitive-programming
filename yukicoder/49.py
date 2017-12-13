s = input()
r, o, l = 0, 0, 0
for c in s:
  if c == '*' or c == '+':
    if l == 0: r += o
    else: r *= o
    l = 0 if c == '*' else 1
    o = 0
  else:
    o = o * 10 + int(c)
if l == 0: r += o
else: r *= o
print(r)

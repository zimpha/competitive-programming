s = [('pfnovu', 'orange'), ('axqwuf', 'cipher'), ('mbgrihcdejkolsty', 'bqsuftlmdxynzvwj')]
mp = {}
for a, b in s:
  for x, y in zip(a, b):
    mp[x] = y
mp['z'] = 'k'
s = input()
t = [mp[x] for x in s]
print(''.join(t))

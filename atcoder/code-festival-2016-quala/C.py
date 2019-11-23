s = input()
k = int(input())
r = []
for c in s:
    n = ord('z') - ord(c) + 1
    if k >= n and c != 'a':
        r.append('a')
        k -= n
    else:
        r.append(c)
if k > 0:
    r[-1] = chr(ord('a') + (ord(r[-1]) - ord('a') + k) % 26)
print(''.join(r))

n = int(input())
candidate = set([str(i) for i in range(10)])
invalid = set()
for i in range(n):
  q = input().split()
  q, r = set(q[:4]), q[-1]
  if r == "YES":
    candidate = candidate.intersection(q)
  else:
    invalid |= q
print(*(candidate - invalid))

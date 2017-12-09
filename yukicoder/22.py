n, k = list(map(int, input().split()))
s = input()
stack = []
mate = [0] * n
for i, c in enumerate(s):
  if c == '(':
    stack.append(i)
  else:
    mate[stack[-1]] = i
    mate[i] = stack[-1]
    stack.pop(-1)
print(mate[k - 1] + 1)

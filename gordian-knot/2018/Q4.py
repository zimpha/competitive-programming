def count(n):
  r = 0
  while n > 1:
    r += n / 2
    n = n / 2 + n % 2
  return r

cnt = 22369621
left, right = 1, cnt * 2
while left < right:
  mid = (left + right - 1) >> 1
  if count(mid) >= cnt:
    right = mid
  else:
    left = mid + 1
print left

cnt = [0] * 10
for i in range(int(input())):
  a, b, c = list(map(int, input().split()))
  cnt[a - 1] += 1
  cnt[b - 1] += 1
  cnt[c - 1] += 1
ret, rem = 0, 0
for i in range(10):
  ret += cnt[i] // 2;
  rem += cnt[i] % 2
print(ret + rem // 4)

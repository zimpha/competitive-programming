#include <cstdio>
#include <map>

using int64 = long long;

std::map<int64, int> cache;

int solve(int64 n) {
  if (n == 0) return 0;
  if (n <= 3) return 1;
  if (cache.count(n)) return cache[n];
  int64 a = 0, b = 1;
  while (true) {
    int64 c = a + b;
    a = b; b = c;
    if (c >= n) break;
  }
  return cache[n] = std::min(solve(n - a), solve(b - n)) + 1;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n;
    scanf("%lld", &n);
    printf("%d\n", solve(n));
  }
  return 0;
}

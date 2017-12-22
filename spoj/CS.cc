#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using int64 = long long;
using pii = std::pair<int, int64>;

int64 pw[18];
pii best;

void dfs(int64 x, int64 y, int dx, int dy, int add, int64 n) {
  if (std::abs(dx - dy) > 2 || n < 0) return;
  if (!n) {
    char s[20];
    sprintf(s, "%lld", x);
    if (strlen(s) != dx) return;
    sprintf(s, "%lld", y);
    if (strlen(s) != dy) return;
    best = std::min(best, {-(dx + dy - 4 + add) / 2, x});
    best = std::min(best, {-(dx + dy - 4 + add) / 2, y});
    return;
  }
  if (dx == dy) {
    if (n % 2 == 0) {
      int d = (n % 10) / 2;
      dfs(x + pw[dx] * d, y + pw[dy] * d, dx + 1, dy + 1, add, (n - 2 * d) / 10);
      d += 5;
      dfs(x + pw[dx] * d, y + pw[dy] * d, dx + 1, dy + 1, add, (n - 2 * d) / 10);
    }
    if (add) {
      for (int d = 0; d < 10; d++) {
        dfs(x, y + pw[dy] * d, dx, dy + 1, add - 1, n - d);
      }
    }
  } else {
    int d = n % 10;
    dfs(x + pw[dx] * d, y + pw[dy] * d, dx + 1, dy + 1, add, (n - d - d * pw[dy - dx]) / 10);
    if (add) {
      dfs(x + pw[dx] * d, y, dx + 1, dy, add - 1, n / 10);
      if (dy - dx < 2) {
        for (int d = 0; d < 10; d++) {
          dfs(x, y + pw[dy] * d, dx, dy + 1, add - 1, n - d * pw[dy - dx]);
        }
      }
    }
  }
}

int64 solve(int64 n) {
  if (!n) return 0;
  best = {1, 1};
  dfs(0, 0, 0, 0, 2, n);
  return best.second;
}

int main() {
  pw[0] = 1;
  for (int i = 1; i < 18; i++) {
    pw[i] = pw[i - 1] * 10;
  }
  for (int64 n; scanf("%lld", &n) == 1;) {
    printf("%lld\n", solve(n));
  }
  return 0;
}

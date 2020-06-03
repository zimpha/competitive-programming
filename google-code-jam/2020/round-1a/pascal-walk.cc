#include <cstdio>
#include <cassert>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::pair<int, int>> path;
    bool found = false;
    for (int tot = 1; tot < 500 && !found; ++tot) {
      for (int one = 1; one < 30 && one <= tot && !found; ++one) {
        int sub = tot - one;
        int nn = n - sub;
        if (nn <= 0) continue;
        if (__builtin_popcount(nn) == one) {
          int mx = -1;
          for (int i = 0; i < 30; ++i) if (nn >> i & 1) mx = i;
          if (mx + 1 > tot) continue;
          int last = -1, rev = 0;
          for (int i = 0; i < 30; ++i) if (nn >> i & 1) {
            ++last;
            while (last < i) {
              if (rev) path.emplace_back(last, last);
              else path.emplace_back(last, 0);
              ++last;
              n -= 1;
            }
            for (int j = 0; j <= last; ++j) {
              if (rev) path.emplace_back(last, last - j);
              else path.emplace_back(last, j);
            }
            n -= 1 << i;
            rev ^= 1;
          }
          ++last;
          while (n > 0) {
            if (rev) path.emplace_back(last, last);
            else path.emplace_back(last, 0);
            ++last;
            --n;
          }
          found = true;
          break;
        }
      }
    }
    assert(found);
    printf("Case #%d:\n", cas);
    for (auto &e: path) {
      printf("%d %d\n", e.first + 1, e.second + 1);
    }
  }
  return 0;
}

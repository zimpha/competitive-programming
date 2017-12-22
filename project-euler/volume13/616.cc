#include <cstdio>
#include <vector>
#include <set>

using int64 = long long;
using int128 = __int128;

int main() {
  const int64 U = 1000000000000;
  const int N = 1000000 + 10;
  std::vector<int> cnt(N, 0);
  for (int i = 2; i < N; ++i) if (!cnt[i]) {
    for (int j = i + i; j < N; j += i) {
      cnt[j] = 1;
    }
  }
  std::set<int64> all;
  for (int64 a = 2; a * a <= U; ++a) {
    int64 x = a * a;
    for (int c = 2; ; ++c) {
      if (cnt[c] || cnt[a]) {
        all.insert(x);
      }
      if ((int128)x * a > U) break;
      x *= a;
    }
  }
  int64 ret = 0;
  for (auto &&x: all) ret += x;
  ret -= 16;
  printf("%lld\n", ret);
  return 0;
}

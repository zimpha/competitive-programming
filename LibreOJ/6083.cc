#include <cstdio>
#include <vector>

using int64 = long long;

int64 S(int n, int m) {
  int64 ret = 0;
  for (int i = 1, j; i <= m; i = j + 1) {
    j = std::min(m, n / (n / i));
    ret += int64(j - i + 1) * (n / i);
  }
  return ret;
}

std::vector<int64> solve(int n) {
  std::vector<int64> cnt(10);
  for (int d = 1; d <= 9; ++d) {
    int64 pw = 1;
    for (int q = 1; q <= 10; ++q) {
      int64 l = d * pw, r = (d + 1) * pw - 1;
      if (l > n) break;
      r = std::min<int64>(r, n);
      cnt[d] += S(n, r) - S(n, l - 1);
      pw = pw * 10;
    }
  }
  return cnt;
}

int main() {
  int l, r;
  scanf("%d%d", &l, &r);
  auto add = solve(r);
  auto sub = solve(l - 1);
  for (int i = 1; i <= 9; ++i) {
    printf("%lld\n", add[i] - sub[i]);
  }
  return 0;
}
#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> p(m);
  for (int i = 0; i < m; ++i) scanf("%d", &p[i]);
  std::vector<int> cnt(n);
  for (int i = 1; i < m; ++i) {
    int l = p[i - 1] - 1, r = p[i] - 1;
    if (l > r) std::swap(l, r);
    cnt[l] += 1;
    cnt[r] -= 1;
  }
  for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
  int64 ret = 0;
  for (int i = 0; i + 1 < n; ++i) {
    int64 a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    ret += std::min(a * cnt[i], b * cnt[i] + c);
  }
  printf("%lld\n", ret);
  return 0;
}

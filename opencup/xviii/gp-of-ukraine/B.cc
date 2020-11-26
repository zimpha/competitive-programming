#include <cstdio>
#include <map>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::map<int, int> cnt;
  for (int i = 0, x; i < m; ++i) {
    scanf("%d", &x);
    cnt[x]++;
  }
  int mx = 0, mv = cnt.rbegin()->first;
  for (auto &e: cnt) {
    if (e.second > mx) mx = e.second;
  }
  int ret = 0;
  for (int d = 1; d * d <= n; ++d) {
    if (n % d != 0) continue;
    if (d >= mv && mx <= n / d) ++ret;
    if (d * d == n) continue;
    if (n / d >= mv && mx <= d) ++ret;
  }
  if (ret == 1) puts("YES");
  else puts("NO");
  return 0;
}

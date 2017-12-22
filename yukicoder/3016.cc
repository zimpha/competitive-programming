#include <cstdio>
#include <map>

using int64 = long long;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::map<int64, int> cnt;
  for (int i = 0; i < n; ++i) {
    int64 x;
    scanf("%lld", &x);
    ++cnt[x];
  }
  for (int i = 0; i < m; ++i) {
    if (i) putchar(' ');
    int64 x;
    scanf("%lld", &x);
    auto it = cnt.find(x);
    if (it == cnt.end()) putchar('0');
    else printf("%d", it->second);
  }
  puts("");
  return 0;
}

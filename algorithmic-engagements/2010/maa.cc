#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 1e6 + 10;

std::pair<int, int> p[N];
std::pair<int, int> f[N], g[N];
int idx[N], xs[N];

int main() {
  int n, d;
  scanf("%d%d", &n, &d);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &p[i].first, &p[i].second);
  }
  std::sort(p, p + n);
  int min = d + 1, max = -1;
  int m = 0;
  for (int i = 0, j; i < n; ) {
    int x = p[i].first;
    for (j = i; j < n && x == p[j].first; ++j) {
      min = std::min(min, p[j].second);
      max = std::max(max, p[j].second);
    }
    while (i < j) idx[i++] = m;
    xs[m] = x;
    f[m++] = {min, max};
  }
  min = d + 1, max = -1;
  for (int i = n - 1, j; i >= 0; i = j) {
    int x = p[i].first;
    for (j = i; j >= 0 && x == p[j].first; --j) {
      min = std::min(min, p[j].second);
      max = std::max(max, p[j].second);
    }
    g[idx[i]] = {min, max};
  }
  int64 ret = 0;
  for (int i = 0; i < m; ++i) {
    if (i > 0 && i + 1 < m) {
      int l = std::max(f[i - 1].first, g[i + 1].first);
      int r = std::min(f[i - 1].second, g[i + 1].second);
      if (l + 1 <= r - 1) ret += r - l - 1;
    }
    if (i > 0) {
      int l = std::max(f[i - 1].first, g[i].first);
      int r = std::min(f[i - 1].second, g[i].second);
      if (l + 1 <= r - 1) ret += int64(r - l - 1) * (xs[i] - xs[i - 1] - 1);
    }
  }
  printf("%lld\n", ret);
  return 0;
}

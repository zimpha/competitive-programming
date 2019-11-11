#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

const int inf = 1e9;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n, -1), b(n - m);
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    a[y - 1] = x;
  }
  for (int i = 0; i < n - m; ++i) scanf("%d", &b[i]);
  int left = 1, right = 1e9;
  while (left < right) {
    int mid = (left + right + 1) >> 1;
    std::vector<int> f(n);
    for (int i = 0; i < n; ++i) {
      if (a[i] == -1) f[i] = 1;
      else if (a[i] >= mid) f[i] = 0;
      else f[i] = inf;
    }
    for (size_t i = 0; i + 2 < f.size(); i += 3) {
      int u[3] = {f[i], f[i + 1], f[i + 2]};
      std::sort(u, u + 3);
      f.push_back(std::min(inf, u[0] + u[1]));
    }
    int cnt = 0;
    for (int i = 0; i < n - m; ++i) cnt += b[i] >= mid;
    if (f.back() <= cnt) left = mid;
    else right = mid - 1;
  }
  printf("%d\n", left);
  return 0;
}

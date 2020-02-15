#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 100 + 10;

int a[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> r(n);
  std::vector<int> c(m);
  for (int i = 0; i < n; ++i) scanf("%d", &r[i]);
  for (int i = 0; i < m; ++i) scanf("%d", &c[i]);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][j] = std::min(r[i], c[j]);
    }
  }
  bool valid = true;
  for (int i = 0; i < n; ++i) {
    int mx = 0;
    for (int j = 0; j < m; ++j) mx = std::max(mx, a[i][j]);
    if (mx != r[i]) valid = false;
  }
  for (int j = 0; j < m; ++j) {
    int mx = 0;
    for (int i = 0; i < n; ++i) mx = std::max(mx, a[i][j]);
    if (mx != c[j]) valid = false;
  }
  if (valid) puts("possible");
  else puts("impossible");
  return 0;
}

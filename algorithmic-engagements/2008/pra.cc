#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

std::vector<std::pair<int, int>> go[N];

int main() {
  int n, m, k, mod;
  scanf("%d%d%d%d", &n, &m, &k, &mod);
  for (int i = 0; i < k; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    go[x - 1].emplace_back(y - 1, 0);
  }
  std::vector<int> u(m);
  for (int i = 0; i < n; ++i) {
    for (auto &e: go[i]) {
      long long w = 1;
      for (int x = e.first - 1; x >= 0; x -= ~x & x + 1) w += u[x];
      e.second = w % mod;
    }
    for (auto &e: go[i]) {
      for (int x = e.first; x < m; x += ~x & x + 1) {
        u[x] += e.second;
        if (u[x] >= mod) u[x] -= mod;
      }
    }
  }
  int ret = 1;
  for (int i = m - 1; i >= 0; i -= ~i & i + 1) {
    ret += u[i];
    if (ret >= mod) ret -= mod;
  }
  printf("%d\n", ret);
  return 0;
}

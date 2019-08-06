#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
    --p[i];
  }
  std::vector<int> ed(n), u(n);
  int lis = 0;
  for (int i = 0; i < n; ++i) {
    ed[i] = 1;
    for (int x = p[i]; x >= 0; x -= ~x & x + 1) {
      ed[i] = std::max(ed[i], u[x] + 1);
    }
    for (int x = p[i]; x < n; x += ~x & x + 1) {
      u[x] = std::max(u[x], ed[i]);
    }
    lis = std::max(lis, ed[i]);
  }
  u.assign(n, 0);
  std::vector<int> ret;
  for (int i = n - 1; i >= 0; --i) {
    int st = 1;
    for (int x = p[i]; x < n; x += ~x & x + 1) {
      st = std::max(st, u[x] + 1);
    }
    for (int x = p[i]; x >= 0; x -= ~x & x + 1) {
      u[x] = std::max(u[x], st);
    }
    if (st + ed[i] == lis + 1) ret.push_back(p[i] + 1);
  }
  std::sort(ret.begin(), ret.end());
  printf("%d\n", (int)ret.size());
  for (auto &x: ret) printf("%d ", x);
  puts("");
  return 0;
}

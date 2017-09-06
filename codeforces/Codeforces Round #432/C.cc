#include <cstdio>
#include <map>
#include <set>

std::map<int, int> sg;

int dfs(int mask) {
  if (sg.count(mask)) return sg[mask];
  std::set<int> all;
  for (int i = 1; i <= 30; ++i) {
    int now = (mask >> i) | (mask & ((1 << i) - 1));
    if (now != mask) {
      all.insert(dfs(now));
    }
  }
  int ret = 0;
  while (all.count(ret)) ++ret;
  return sg[mask] = ret;
}

int main() {
  int n;
  std::map<int, int> mask;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    for (int d = 2; d * d <= x; ++d) {
      if (x % d) continue;
      int e = 0;
      while (x % d == 0) x /= d, ++e;
      mask[d] |= 1 << e;
    }
    if (x > 1) mask[x] |= 2;
  }
  int ret = 0;
  for (auto &&e: mask) {
    ret ^= dfs(e.second);
  }
  if (ret) puts("Mojtaba");
  else puts("Arpa");
  return 0;
}
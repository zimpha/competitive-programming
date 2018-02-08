#include <cstdio>
#include <vector>
#include <functional>
#include <map>

using pii = std::pair<int, int>;

std::map<pii, int> cache;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> dsu(n * 2);
  for (int i = 0; i < n * 2; ++i) dsu[i] = i;
  std::function<int(int)> root = [&](int x) {
    if (x != dsu[x]) dsu[x] = root(dsu[x]);
    return dsu[x];
  };
  int m = 0;
  for (int i = 0; i < n; ++i) {
    pii a, b;
    scanf("%d%d%d%d", &a.first, &a.second, &b.first, &b.second);
    if (!cache.count(a)) cache[a] = m++;
    if (!cache.count(b)) cache[b] = m++;
    int x = root(cache[a]);
    int y = root(cache[b]);
    if (x == y) {
      printf("%d\n", i + 1);
      return 0;
    }
    dsu[x] = y;
  }
  puts("0");
  return 0;
}

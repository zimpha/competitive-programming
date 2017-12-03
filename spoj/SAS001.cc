#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, p;
  scanf("%d%d", &n, &p);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  auto xs = a;
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  for (auto &&x: a) {
    x = std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
  }
  int m = xs.size();
  std::vector<int> bit(m);
  auto add = [&bit, &m](int x, int v) {
    for (; x < m; x += ~x & x + 1) bit[x] += v;
  };
  auto get = [&bit, &m](int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += bit[x];
    return r;
  };
  long long now = 0, ret = -1;
  int index = -1, cnt = 0;
  for (int i = 0; i < p - 1; ++i) {
    now += cnt - get(a[i]);
    add(a[i], 1);
    ++cnt;
  }
  for (int i = p - 1; i < n; ++i) {
    now += cnt - get(a[i]);
    add(a[i], 1);
    ++cnt;
    if (now > ret || (now == ret && i < index)) {
      ret = now;
      index = i;
    }
    now -= get(a[i - p + 1] - 1);
    add(a[i - p + 1], -1);
    --cnt;
  }
  printf("%d %lld\n", index - p + 2, ret);
  return 0;
}

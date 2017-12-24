#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

int bit[N], m;

void add(int x, int v) {
  for (; x <= m; x += ~x & x + 1) bit[x] += v;
}

int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<int64> s(n + 1);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &s[i]);
    s[i] += s[i - 1];
  }
  for (int i = 0; i <= n; ++i) {
    s[i] -= (int64)i * k;
  }
  auto xs = s;
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  m = xs.size();
  int64 ret = 0;
  for (int i = 0; i <= n; ++i) {
    s[i] = std::lower_bound(xs.begin(), xs.end(), s[i]) - xs.begin();
    ret += get(s[i]);
    add(s[i], 1);
  }
  printf("%lld\n", ret);
  return 0;
}

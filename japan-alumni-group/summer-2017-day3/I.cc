#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10;

using int64 = long long;

std::pair<int, int> p[N], q[N];
int n, c;

int64 solve(int l, int r) {
  if (l + 1 == r) return 0;
  int m = (l + r) >> 1;
  int64 ret = solve(l, m) + solve(m, r);
  std::vector<int> xs;
  for (int i = l; i < r; ++i) {
    xs.push_back(p[i].second);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  std::vector<int64> bit(xs.size()), cnt(xs.size());
  auto add = [&bit, &cnt](int x, int v) {
    for (; x < bit.size(); x += ~x & x + 1) {
      bit[x] += v;
      cnt[x] += 1;
    }
  };
  auto get = [&bit, &cnt](int x, int64 r = 0, int r2 = 0) {
    for (; x >= 0; x -= ~x & x + 1) {
      r += bit[x];
      r2 += cnt[x];
    }
    return std::make_pair(r, r2);
  };
  int x = l, y = m, i = l;
  int64 sum_w = 0;
  for (int it = l; it < r; ++it) {
    if (x == m || (y < r && p[y].first < p[x].first)) {
      int id = std::lower_bound(xs.begin(), xs.end(), p[y].second) - xs.begin();
      add(id, p[y].second);
      sum_w += p[y].second;
      q[i++] = p[y++];
    } else {
      int id = std::lower_bound(xs.begin(), xs.end(), p[x].second) - xs.begin();
      auto lt = get(id);
      ret += (int64)c * lt.first + (int64)lt.second * p[x].second;
      ret += (int64)c * p[x].second * (y - m - lt.second) + sum_w - lt.first;
      q[i++] = p[x++];
    }
  }
  for (int i = l; i < r; ++i) {
    p[i] = q[i];
  }
  return ret;
}

int main() {
  scanf("%d%d", &n, &c);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &p[i].first, &p[i].second);
  }
  printf("%lld\n", solve(0, n));
  return 0;
}

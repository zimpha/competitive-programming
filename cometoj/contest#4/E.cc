#include <cstdio>
#include <vector>
#include <algorithm>

int solve1(const std::vector<int> &a, const std::vector<int> &b, int e) {
  int ca = 0, cb = 0;
  for (auto &&x: a) ca += x == e;
  for (auto &&x: b) cb += x == e;
  return std::min(ca, cb);
}

int solve2(const std::vector<int> &a, const std::vector<int> &b, int x, int y) {
  int say = 0, sby = 0;
  for (auto &v: a) say += v == y;
  for (auto &v: b) sby += v == y;
  int ret = 0;
  for (size_t i = 0, j = 0, cx = 0; i < a.size() && j < b.size(); ++i, ++j) {
    while (i < a.size() && a[i] != x) {
      say -= a[i] == y;
      ++i;
    }
    while (j < b.size() && b[j] != x) {
      sby -= b[j] == y;
      ++j;
    }
    if (i < a.size() && a[i] == x && j < b.size() && b[j] == x) {
      ++cx;
      ret = std::max<int>(ret, cx + std::min(say, sby));
    }
  }
  return ret;
}

int solve(const std::vector<int> &a, const std::vector<int> &b) {
  std::vector<int> sa1(a.size() + 1), sb1(b.size() + 1);
  for (int i = a.size() - 1; i >= 0; --i) {
    sa1[i] = sa1[i + 1] + (a[i] == 1);
  }
  for (int i = b.size() - 1; i >= 0; --i) {
    sb1[i] = sb1[i + 1] + (b[i] == 1);
  }
  std::vector<int> pa0, pa2, pb0, pb2;
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == 0) pa0.push_back(i);
    if (a[i] == 2) pa2.push_back(i);
  }
  for (size_t i = 0; i < b.size(); ++i) {
    if (b[i] == 0) pb0.push_back(i);
    if (b[i] == 2) pb2.push_back(i);
  }
  pa2.push_back(a.size());
  pb2.push_back(b.size());
  std::reverse(pa2.begin(), pa2.end());
  std::reverse(pb2.begin(), pb2.end());
  std::vector<int> xs;
  for (size_t i = 0; i < pa2.size() && i < pb2.size(); ++i) {
    xs.push_back(sa1[pa2[i]] - sb1[pb2[i]]);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());

  std::vector<int> bit(xs.size(), -1e9);

  auto add = [](std::vector<int> &bit, int x, int v) {
    for (; x >= 0; x -= ~x & x + 1) {
      bit[x] = std::max(bit[x], v);
    }
  };

  auto get = [](std::vector<int> &bit, int x, int r = -1e9) {
    for (; x < bit.size(); x += ~x & x + 1) {
      r = std::max(bit[x], r);
    }
    return r;
  };

  int ret = 0;
  for (int i = std::min(pa0.size(), pb0.size()) - 1, j = 0; i >= 0; --i) {
    while (j < pa2.size() && j < pb2.size() && pa2[j] > pa0[i] && pb2[j] > pb0[i]) {
      int p = std::lower_bound(xs.begin(), xs.end(), sa1[pa2[j]] - sb1[pb2[j]]) - xs.begin();
      add(bit, p, j - sa1[pa2[j]]);
      ++j;
    }
    auto p = std::lower_bound(xs.begin(), xs.end(), sa1[pa0[i]] - sb1[pb0[i]]) - xs.begin();
    ret = std::max(ret, sa1[pa0[i]] + get(bit, p) + i + 1);
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      --a[i];
    }
    for (int i = 0; i < m; ++i) {
      scanf("%d", &b[i]);
      --b[i];
    }
    int res = std::max(std::max(solve1(a, b, 0), solve1(a, b, 1)), solve1(a, b, 2));
    res = std::max(res, solve2(a, b, 0, 1));
    res = std::max(res, solve2(a, b, 0, 2));
    res = std::max(res, solve2(a, b, 1, 2));
    res = std::max(res, solve(a, b));
    res = std::max(res, solve(b, a));
    printf("%d\n", res);
  }
  return 0;
}

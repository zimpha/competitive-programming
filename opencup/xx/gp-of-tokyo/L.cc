#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 10;

struct point {
  int x, y, w;
  bool operator < (const point &rhs) const {
    return y < rhs.y;
  }
};

std::vector<int> query[N];
int bits[N];

int main() {
  int n, q;
  scanf("%d", &n);
  std::vector<point> red(n), blue(n);
  std::vector<int> xs;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &red[i].x, &red[i].y, &red[i].w);
    xs.push_back(red[i].x);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &blue[i].x, &blue[i].y, &blue[i].w);
    xs.push_back(blue[i].x);
  }

  std::sort(xs.begin(), xs.end());
  for (int i = 0; i < n; ++i) {
    red[i].x = std::lower_bound(xs.begin(), xs.end(), red[i].x) - xs.begin();
    blue[i].x = std::lower_bound(xs.begin(), xs.end(), blue[i].x) - xs.begin();
  }

  std::sort(red.begin(), red.end());
  std::sort(blue.begin(), blue.end());
  std::vector<std::pair<int, int>> good;
  std::vector<int> prefix(n), suffix(n), next(n);
  for (int i = 0; i < n; ++i) {
    prefix[i] = i ? prefix[i - 1] : i;
    if (red[i].w > red[prefix[i]].w) prefix[i] = i;
  }
  for (int i = n - 1; i >= 0; --i) {
    suffix[i] = i == n - 1 ? i : suffix[i + 1];
    if (blue[i].w > blue[suffix[i]].w) suffix[i] = i;
  }
  for (int i = n - 1; i >= 0; --i) {
    int j = i + 1;
    while (j < n && red[j].w <= red[i].w) j = next[j];
    next[i] = j;
  }
  for (int i = 0, j = 0; i < n; ++i) {
    while (j < n && blue[j].y < red[i].y) ++j;
    if (j != n) good.emplace_back(i, suffix[j]);
  }
  for (int i = 0, j = 0; i < n; ++i) if (prefix[i] == i && next[i] != n) {
    while (j < n && blue[j].y < red[next[i]].y) ++j;
    if (j != n) good.emplace_back(i, suffix[j]);
  }
  for (int j = n - 1, i = n - 1; j >= 0; --j) {
    while (i >= 0 && red[i].y > blue[j].y) --i;
    if (i >= 0) good.emplace_back(prefix[i], j);
  }
  std::sort(good.begin(), good.end(), [&](auto &a, auto &b) {
    return red[a.first].x < red[b.first].x;
  });

  scanf("%d", &q);
  std::vector<int> L(q), R(q), ret(q);
  for (int i = 0; i < q; ++i) scanf("%d%d", &L[i], &R[i]);

  // first pass
  for (int i = 0; i < n * 2; ++i) query[i].clear();
  for (int i = 0; i < n * 2; ++i) bits[i] = 0;
  for (int i = 0; i < q; ++i) {
    auto x = std::lower_bound(xs.begin(), xs.end(), L[i]) - xs.begin();
    if (x != 0) query[x - 1].push_back(i);
  }
  for (size_t i = 0, j = 0; i < xs.size(); ++i) {
    while (j < good.size() && red[good[j].first].x <= i) {
      int w = red[good[j].first].w + blue[good[j].second].w;
      for (int x = blue[good[j].second].x; x >= 0; x -= ~x & x + 1) {
        bits[x] = std::max(bits[x], w);
      }
      ++j;
    }
    for (auto &idx: query[i]) {
      int x = std::lower_bound(xs.begin(), xs.end(), R[idx]) - xs.begin();
      for (; x <= n * 2; x += ~x & x + 1) {
        ret[idx] = std::max(ret[idx], bits[x]);
      }
    }
  }
  // second pass
  for (int i = 0; i < n * 2; ++i) query[i].clear();
  for (int i = 0; i < n * 2; ++i) bits[i] = 0;
  for (int i = 0; i < q; ++i) {
    auto x = std::lower_bound(xs.begin(), xs.end(), L[i]) - xs.begin();
    if (x != n * 2) query[x].push_back(i);
  }
  for (int i = n * 2 - 1, j = good.size() - 1; i >= 0; --i) {
    while (j >= 0 && red[good[j].first].x >= i) {
      int w = red[good[j].first].w + blue[good[j].second].w;
      for (int x = blue[good[j].second].x; x <= n * 2; x += ~x & x + 1) {
        bits[x] = std::max(bits[x], w);
      }
      --j;
    }
    for (auto &idx: query[i]) {
      int x = std::lower_bound(xs.begin(), xs.end(), R[idx]) - xs.begin();
      for (x -= 1; x >= 0; x -= ~x & x + 1) {
        ret[idx] = std::max(ret[idx], bits[x]);
      }
    }
  }

  for (int i = 0; i < q; ++i) {
    if (ret[i] == 0) ret[i] = -1;
    printf("%d\n", ret[i]);
  }
  return 0;
}

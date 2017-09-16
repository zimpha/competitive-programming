#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

struct flight_t {
  int d, f, c;
  flight_t() = default;
  flight_t(int d, int f, int c): d(d), f(f), c(c) {}
  bool operator < (const flight_t &rhs) const {
    return d < rhs.d;
  }
};

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  std::vector<flight_t> in, out;
  int mx = 0;
  for (int i = 0; i < m; ++i) {
    int d, f, t, c;
    scanf("%d%d%d%d", &d, &f, &t, &c);
    if (f == 0) out.emplace_back(d, t - 1, c);
    else in.emplace_back(d, f - 1, c);
    mx = std::max(mx, d + 1);
  }
  std::sort(in.begin(), in.end());
  std::sort(out.begin(), out.end());
  std::reverse(out.begin(), out.end());
  std::vector<int64> pre(mx + 1, -1), suf(mx + 1, -1);
  std::vector<int> cost(n, -1);
  int64 cnt = 0, total = 0;
  for (int i = 1, j = 0; i <= mx; ++i) {
    while (j < in.size() && in[j].d == i) {
      int v = in[j].f, c = in[j].c;
      if (cost[v] == -1) {
        ++cnt;
        cost[v] = c;
        total += cost[v];
      } else if (c < cost[v]) {
        total -= cost[v];
        cost[v] = c;
        total += cost[v];
      }
      ++j;
    }
    if (cnt == n) pre[i] = total;
  }
  cost.assign(n, -1);
  cnt = total = 0;
  for (int i = mx, j = 0; i >= 1; --i) {
    while (j < out.size() && out[j].d == i) {
      int v = out[j].f, c = out[j].c;
      if (cost[v] == -1) {
        ++cnt;
        cost[v] = c;
        total += cost[v];
      } else if (c < cost[v]) {
        total -= cost[v];
        cost[v] = c;
        total += cost[v];
      }
      ++j;
    }
    if (cnt == n) suf[i] = total;
  }
  int64 ret = -1;
  for (int i = 1; i + k < mx; ++i) {
    if (pre[i] != -1 && suf[i + k + 1] != -1) {
      int64 total = pre[i] + suf[i + k + 1];
      if (ret == -1 || total < ret) ret = total;
    }
  }
  printf("%lld\n", ret);
  return 0;
}
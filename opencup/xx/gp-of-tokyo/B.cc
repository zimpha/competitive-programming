#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;

int64 a[N], sum[N], ssum[N];
int64 ret[N], s;
int ql[N], qr[N];
int bound[N], n, q;

int64 cost(int x, int y) {
  if (bound[x] == 0) return 0;
  int len = std::min(x - y, bound[x] - 1);
  int64 rest = s - (sum[x + len] - sum[x - len - 1]);
  int64 ret = x * sum[x] - ssum[x] - (x * sum[x - len - 1] - ssum[x - len - 1]);
  ret += ssum[x + len] - sum[x + len] * x - (ssum[x] - sum[x] * x);
  ret += rest * (len + 1);
  return ret;
}

void prepare() {
  sum[0] = a[0]; ssum[0] = 0;
  for (int i = 1; i <= n + 1; ++i) {
    sum[i] = sum[i - 1] + a[i];
    ssum[i] = ssum[i - 1] + a[i] * i;
  }
  for (int i = 1; i <= n; ++i) {
    int left = 0, right = std::min(i, n + 1 - i);
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      if (sum[i + mid] - ((i - mid) ? sum[i - mid - 1] : 0) >= s) right = mid;
      else left = mid + 1;
    }
    bound[i] = right;
  }
}

namespace hull {
std::vector<int> query[N];
void solve() {
  for (int i = 1; i <= n; ++i) query[i].clear();
  for (int i = 0; i < q; ++i) {
    query[(ql[i] + qr[i]) / 2].push_back(i);
  }
  std::vector<std::pair<int, int>> hull;
  for (int x = 1; x <= n; ++x) {
    while (!hull.empty() && cost(x, hull.back().first) > cost(hull.back().second, hull.back().first)) {
      hull.pop_back();
    }
    if (hull.empty()) hull.emplace_back(1, x);
    else {
      int l = hull.back().first, r = x - 1;
      while (l < r) {
        int m = (l + r - 1) >> 1;
        auto c1 = cost(hull.back().second, m);
        auto c2 = cost(x, m);
        if (c2 >= c1) r = m;
        else l = m + 1;
      }
      hull.emplace_back(r, x);
    }
    for (auto &idx: query[x]) {
      auto it = std::upper_bound(hull.begin(), hull.end(), std::make_pair(ql[idx], N)) - 1;
      assert(it->first <= ql[idx]);
      ret[idx] = std::max(ret[idx], cost(it->second, ql[idx]));
    }
  }
}
}

namespace smawk {
std::vector<int> query[N];
void solve() {
  for (int len = 1; len <= n + 2; len <<= 1) {
    for (int i = 1; i <= n; ++i) query[i].clear();
    for (int i = 0; i < q; ++i) {
      int l = (ql[i] + len - 1) / len, r = ((ql[i] + qr[i]) / 2 + 1) / len;
      if (l >= r) continue;
      if (l & 1) query[l].push_back(i);
      if (r & 1) query[r - 1].push_back(i);
    }
    for (int i = 0; i < n + 2; i += len) {
      auto &ls = query[i / len];
      if (ls.empty()) continue;
      std::sort(ls.begin(), ls.end(), [&](int x, int y) {
        return ql[x] < ql[y];
      });

      auto dfs = [&](auto self, int l, int r, int xl, int xr) {
        if (l > r) return;
        int m = (l + r) >> 1;
        int64 best = -1;
        int xm = -1;
        for (int x = xl; x <= xr; ++x) {
          assert(x >= ql[ls[m]]);
          auto now = cost(x, ql[ls[m]]);
          if (now > best) best = now, xm = x;
        }
        ret[ls[m]] = std::max(ret[ls[m]], best);
        self(self, l, m - 1, xl, xm);
        self(self, m + 1, r, xm, xr);
      };

      dfs(dfs, 0, ls.size() - 1, i, std::min(i + len - 1, n + 1));
    }
  }
}
}

int main() {
  scanf("%d%lld", &n, &s);
  a[0] = a[n + 1] = s;
  for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d", &ql[i], &qr[i]);
    if (ql[i] > qr[i]) std::swap(ql[i], qr[i]);
  }
  prepare();
  hull::solve();
  std::reverse(a, a + n + 2);
  for (int i = 0; i < q; ++i) {
    ql[i] = n + 1 - ql[i];
    qr[i] = n + 1 - qr[i];
    std::swap(ql[i], qr[i]);
  }
  prepare();
  hull::solve();
  for (int i = 0; i < q; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}

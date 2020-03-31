#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> l(n), r(n), xs;
    xs.reserve(n * 6);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &l[i], &r[i]);
      xs.push_back(l[i]);
      xs.push_back(l[i] - 1);
      xs.push_back(l[i] + 1);
      xs.push_back(r[i]);
      xs.push_back(r[i] - 1);
      xs.push_back(r[i] + 1);
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    int m = xs.size();
    std::vector<std::vector<int>> ivs(m);
    std::vector<int> sum(m);
    for (int i = 0; i < n; ++i) {
      l[i] = std::lower_bound(xs.begin(), xs.end(), l[i]) - xs.begin();
      r[i] = std::lower_bound(xs.begin(), xs.end(), r[i]) - xs.begin();
      ivs[r[i]].push_back(l[i]);
    }
    std::vector<int> sol;
    for (int i = 0; i < m; ++i) {
      if (i) sum[i] = sum[i - 1];
      for (auto e: ivs[i]) {
        int now = sum[i] - (e ? sum[e - 1] : 0);
        if (now == 0) sum[i] += 1, sol.push_back(xs[i]);
      }
      ivs[i].clear();
    }
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      int now = sum[r[i]] - (l[i] ? sum[l[i] - 1] : 0);
      ret = std::max(ret, now);
    }
    const int LOG = 21;
    std::vector<std::vector<int>> go(LOG, std::vector<int>(m, -1));

    auto jump = [&](int x, int len) {
      for (int i = LOG - 1; i >= 0; --i) {
        if (len >> i & 1) x = go[i][x];
        if (x == -1) return m;
      }
      return x;
    };

    if (ret > 1) {
      std::vector<int> max_r(m);
      for (int i = 0; i < n; ++i) {
        max_r[l[i]] = std::max(max_r[l[i]], r[i]);
        ivs[l[i]].push_back(r[i]);
      }
      for (int i = 1; i < m; ++i) {
        max_r[i] = std::max(max_r[i - 1], max_r[i]);
      }
      std::vector<int> good = {m - 1};
      int min_r = m;
      for (int i = m - 2; i >= 0; --i) {
        auto it = std::upper_bound(good.rbegin(), good.rend(), min_r);
        if (it != good.rbegin()) {
          --it;
          if (jump(*it, ret - 2) > max_r[i]) {
            go[0][i] = *it;
            good.push_back(i);
            for (int j = 1; j < LOG; ++j) if (go[j - 1][i] != -1) {
              go[j][i] = go[j - 1][go[j - 1][i]];
            }
          }
        }
        for (auto r: ivs[i]) min_r = std::min(min_r, r);
      }
      if (good.back() == 0) {
        --ret;
        sol.clear();
        for (int x = go[0][0]; x != -1; x = go[0][x]) {
          sol.push_back(xs[x]);
        }
      }
    }
    printf("%d %d", ret, (int)sol.size());
    for (auto &x: sol) printf(" %d", x);
    puts("");
  }
  return 0;
}

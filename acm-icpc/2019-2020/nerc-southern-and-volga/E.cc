#include <cstdio>
#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>

using int64 = long long;

const int N = 100;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    std::vector<int64> p(n), q(n);
    for (int i = 0; i < n; ++i) {
      scanf("%s", s);
      for (int j = 0; j < m; ++j) {
        if (s[j] == '1') {
          p[i] |= int64(1) << j;
          q[i] |= int64(1) << (m - 1 - j);
        }
      }
    }
    std::vector<std::vector<std::pair<int, int>>> edges(n);
    bool valid = true;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        auto x = (m - __builtin_popcountll(p[i] ^ p[j])) >= k;
        auto y = (m - __builtin_popcountll(p[i] ^ q[j])) >= k;
        if (!x && !y) valid = false;
        if (!x && y) {
          edges[i].emplace_back(j, 1);
          edges[j].emplace_back(i, 1);
        }
        if (x && !y) {
          edges[i].emplace_back(j, 0);
          edges[j].emplace_back(i, 0);
        }
      }
    }

    std::vector<int> col(n, -1);
    std::vector<int> cnt[2];

    std::function<bool(int, int)> dfs = [&](int u, int c) {
      if (col[u] != -1) return col[u] == c;
      cnt[c].push_back(u);
      col[u] = c;
      for (auto &e: edges[u]) {
        if (!dfs(e.first, c ^ e.second)) return false;
      }
      return true;
    };

    std::vector<int> ret;
    for (int i = 0; i < n; ++i) if (col[i] == -1) {
      cnt[0].clear();
      cnt[1].clear();
      if (!dfs(i, 0)) {
        valid = false;
        break;
      }
      if (cnt[0].size() > cnt[1].size()) {
        std::swap(cnt[0], cnt[1]);
      }
      for (auto &x: cnt[0]) ret.push_back(x);
    }
    if (!valid) puts("-1");
    else {
      printf("%d\n", (int)ret.size());
      for (size_t i = 0; i < ret.size(); ++i) {
        if (i) putchar(' ');
        std::swap(p[ret[i]], q[ret[i]]);
        printf("%d", ret[i] + 1);
      }
      puts("");
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
          assert(m - __builtin_popcount(p[i] ^ p[j]) >= k);
        }
      }
    }
  }
  return 0;
}

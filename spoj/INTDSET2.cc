#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#include <map>

const int mod = 1e9 + 7;

inline void upd(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    std::map<int, int> mp;
    int n, m = 0;
    scanf("%d", &n);
    std::vector<int> l(n), r(n), pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i - 1] % mod;
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &l[i], &r[i]);
      mp[r[i]] = 0;
    }
    std::vector<int> val;
    for (auto &x: mp) {
      val.push_back(x.first);
      x.second = m++;
    }
    assert(m <= 15);
    std::vector<std::vector<int>> S(m);
    for (int i = 0; i < n; ++i) {
      S[mp[r[i]]].push_back(l[i]);
    }
    for (int i = 0; i < m; ++i) {
      std::sort(S[i].begin(), S[i].end());
    }
    std::vector<int> f(1 << m, 0), g(1 << m, 0);
    f[0] = 1;
    for (int i = m - 1; i >= 0; --i) {
      f.swap(g); f.assign(1 << m, 0);
      std::vector<int> &v = S[i];
      for (int msk = 0; msk < (1 << m); ++msk) if (g[msk]) {
        upd(f[msk], g[msk]); // ignore i
        int ns = 0;
        for (int j = i; j < m; ++j) if (S[j].back() <= val[i]) ns |= 1 << j;
        for (int j = i; j >= 0; --j) {// cover [j, i]
          ns |= 1 << j;
          if (*v.begin() > val[j]) break;
          // v[r] <= val[j], v[l] > val[j - 1];
          int l = std::upper_bound(v.begin(), v.end(), j ? val[j - 1] : 0) - v.begin();
          int r = std::upper_bound(v.begin(), v.end(), val[j]) - v.begin() - 1;
          if (l > r) continue;
          upd(f[msk | ns], 1ll * (pw[r - l + 1] - 1) * pw[v.size() - r - 1] % mod * g[msk] % mod);
        }
      }
    }
    printf("%d\n", f[(1 << m) - 1]);
  }
  return 0;
}

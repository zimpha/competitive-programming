#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

using int64 = long long;

const int N = 5e4 + 10, Q = 2e5 + 10;
const int mod = 1e9 + 7;

int st[Q], ed[Q];
int64 ret[Q], tot[N];
int a[N], cnt[N][20][20];
int n, m, k;

namespace mo {
  int64 cnt[21][21];
  void init() {
    memset(cnt, 0, sizeof(cnt));
  }
  void add_l(int x) {
    for (int i = x; i < k; ++i) cnt[x][i] *= 2;
    cnt[x][x]++;
    for (int i = x + 1; i < k; ++i) {
      for (int j = i; j < k; ++j) {
        cnt[x][j] += cnt[i][j];
      }
    }
    for (int i = x; i < k; ++i) cnt[x][i] %= mod;
  }
  void add_r(int x) {
    for (int i = 0; i <= x; ++i) cnt[i][x] *= 2;
    cnt[x][x]++;
    for (int i = 0; i < x; ++i) {
      for (int j = i; j < x; ++j) {
        cnt[i][x] += cnt[i][j];
      }
    }
    for (int i = 0; i <= x; ++i) cnt[i][x] %= mod;
  }
}

void solve(int l, int r, const std::vector<int> &all) {
  if (l + 1 == r) {
    for (auto &x: all) ret[x] = 2; 
    return;
  }
  int m = (l + r) >> 1;
  std::vector<int> left, right;
  for (auto &x: all) {
    if (ed[x] <= m) left.push_back(x);
    if (st[x] >= m) right.push_back(x);
  }
  solve(l, m, left);
  solve(m, r, right);
  mo::init();
  for (int i = m - 1; i >= l; --i) {
    mo::add_l(a[i]);
    tot[i] = 0;
    for (int x = 0; x < k; ++x) {
      for (int y = x; y < k; ++y) {
        cnt[i][x][y] = mo::cnt[x][y];
        tot[i] += mo::cnt[x][y];
      }
    }
  }
  mo::init();
  for (int i = m; i < r; ++i) {
    mo::add_r(a[i]);
    tot[i] = 0;
    for (int x = 0; x < k; ++x) {
      for (int y = x; y < k; ++y) {
        cnt[i][x][y] = mo::cnt[x][y];
        tot[i] += mo::cnt[x][y];
      }
    }
  }
  for (auto &x: all) if (st[x] < m && ed[x] > m) {
    int l = st[x], r = ed[x] - 1;
    ret[x] = tot[l] + tot[r] + 1;
    int64 p[20][20], q[20];
    memset(p, 0, sizeof(p));
    memset(q, 0, sizeof(q));
    for (int a = 0; a < k; ++a) {
      for (int b = a; b < k; ++b) {
        p[a][b] = cnt[l][a][b];
        q[a] += cnt[r][a][b];
        if (b > a) p[a][b] += p[a][b - 1];
      }
      q[a] %= mod;
    }
    for (int a = 0; a < k; ++a) {
      for (int b = a; b < k; ++b) {
        ret[x] += (p[a][b] % mod) * q[b] % mod;
      }
    }
    ret[x] %= mod;
  }
}

void run() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
    --a[i];
  }
  scanf("%d", &m);
  std::vector<int> all;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &st[i], &ed[i]);
    --st[i];
    all.push_back(i);
  }
  solve(0, n, all);
  for (int i = 0; i < m; ++i) {
    printf("%lld\n", ret[i]);
  }
}

int main() {
  freopen("nondec.in", "r", stdin);
  freopen("nondec.out", "w", stdout);
  run();
  return 0;
}

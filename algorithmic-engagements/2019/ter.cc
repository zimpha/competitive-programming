#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>

using int64 = long long;
const int N = 1e6 + 10;
const int seed1 = 671141, seed2 = 10627;
const int mod1 = 1000000021, mod2 = 1000000087;

std::pair<int, int> ev[N], x[N], y[N];
std::pair<int64, int> val[N];
int64 p1[N], p2[N], coef[N];

int solve(std::pair<int, int>* seg, int n, int B) {
  p1[0] = p2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    coef[i] = rand() % 1000000007;
    p1[i] = p1[i - 1] * seed1 % mod1;
    p2[i] = p2[i - 1] * seed2 % mod2;
  }
  int ret = B, m = 0;
  for (int i = 0; i < n; ++i) {
    int l = seg[i].first, r = seg[i].second;
    if (l > r) std::swap(l, r);
    ev[m++] = {l, +(i + 1)};
    ev[m++] = {r, -(i + 1)};
  }
  std::sort(ev, ev + m);
  int64 h1 = 0, h2 = 0;
  int vs = 0;
  for (int i = 0, j, c = 0; i < m; i = j) {
    for (j = i; j < m && ev[i].first == ev[j].first; ++j) {
      int idx = ev[j].second > 0 ? ev[j].second : -ev[j].second;
      if (ev[j].second > 0) h1 += coef[idx] * p1[idx] % mod1;
      else h1 -= coef[idx] * p1[idx] % mod1;
      if (ev[j].second > 0) h2 += coef[idx] * p2[idx] % mod1;
      else h2 -= coef[idx] * p2[idx] % mod1;
      if (ev[j].second > 0) ++c;
      else --c;
    }
    h1 %= mod1; if (h1 < 0) h1 += mod1;
    h2 %= mod2; if (h2 < 0) h2 += mod2;
    if (c) {
      val[vs++] = {h1 * mod2 + h2, ev[j].first - ev[i].first};
      ret -= val[vs - 1].second;
    } else {
      assert(h1 == 0 && h2 == 0);
    }
  }
  if (ret) val[vs++] = {0, ret};
  std::sort(val, val + vs);
  for (int i = 0, j; i < vs; i = j) {
    int cnt = 0;
    for (j = i; j < vs && val[i].first == val[j].first; ++j) {
      cnt += val[j].second;
    }
    ret = std::max(ret, cnt);
  }
  return ret;
}

int main() {
  srand(time(NULL));
  int n, X, Y;
  scanf("%d%d%d", &n, &X, &Y);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d%d", &x[i].first, &y[i].first, &x[i].second, &y[i].second);
  }
  printf("%lld\n", 1ll * solve(x, n, X) * solve(y, n, Y));
  return 0;
}

#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using u64 = unsigned long long;
using i64 = long long;

const int N = 3e5 + 10;
const int mod1 = 1e9 + 7, mod2 = 998244353;
const int seed1 = 65537, seed2 = 1e6 + 3;
const int mod = 998244353;

i64 pw1[N], pw2[N];
i64 hs1[N], hs2[N];
i64 fac[N], ifac[N];
u64 xs[N * 2];
int pos[N];
char s[N];

i64 pow_mod(i64 a, i64 n) {
  i64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

i64 get_hash(int i, int x) {
  i64 h1 = (hs1[i] - hs1[i + x] * pw1[x] % mod1 + mod1) % mod1;
  i64 h2 = (hs2[i] - hs2[i + x] * pw2[x] % mod2 + mod2) % mod2;
  return (h1 << 31) + h2;
}

int main() {
  pw1[0] = pw2[0] = fac[0] = ifac[0] = 1;
  for (int i = 1; i < N; ++i) {
    pw1[i] = pw1[i - 1] * seed1 % mod1;
    pw2[i] = pw2[i - 1] * seed2 % mod2;
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s", s);
    int n = strlen(s);
    //int n = 300000;
    //for (int i = 0; i < n; ++i) s[i] = 'a' + __builtin_popcount(i);
    hs1[n] = hs2[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      hs1[i] = (hs1[i + 1] * seed1 + s[i]) % mod1;
      hs2[i] = (hs2[i + 1] * seed2 + s[i]) % mod2;
    }

    i64 ret = 0;
    for (int d = 1; d <= n; ++d) {
      if (n % d == 0) {
        std::vector<i64> hs(n / d);
        for (int i = 0; i < n; i += d) {
          hs[i / d] = get_hash(i, d);
        }
        std::sort(hs.begin(), hs.end());
        i64 now = fac[n / d];
        for (int i = 0, j; i < n / d; i = j) {
          for (j = i; j < n / d && hs[i] == hs[j]; ++j);
          now = now * ifac[j - i] % mod;
        }
        ret += now;
      } else {
        int r = n % d;
        std::vector<std::pair<u64, int>> all(n / d + 1);
        std::vector<u64> hs(n / d + 1), cnt(n / d * 2 + 1);
        u64 state = 0, ways = fac[n / d];

        int m = 0;
        for (int i = r; i + d <= n; i += d) {
          xs[m++] = get_hash(i, d);
        }
        for (int i = 0; i + d <= n; i += d) {
          xs[m++] = get_hash(i, d);
        }
        std::sort(xs, xs + m);
        m = std::unique(xs, xs + m) - xs;
        for (int i = r; i + d <= n; i += d) {
          pos[i] = std::lower_bound(xs, xs + m, get_hash(i, d)) - xs;
        }
        for (int i = 0; i + d <= n; i += d) {
          pos[i] = std::lower_bound(xs, xs + m, get_hash(i, d)) - xs;
        }

        auto add = [&](int idx, int v) {
          u64 h = xs[idx];
          int nc = cnt[idx];
          if (nc) state -= pw1[nc] * hs[nc];
          ways = ways * fac[nc] % mod;
          hs[nc] ^= h;
          if (nc) state += pw1[nc] * hs[nc];
          nc += v;
          if (nc) state -= pw1[nc] * hs[nc];
          hs[nc] ^= h;
          if (nc) state += pw1[nc] * hs[nc];
          ways = ways * ifac[nc] % mod;
          cnt[idx] = nc;
        };

        for (int i = r; i + d <= n; i += d) {
          add(pos[i], 1);
        }
        all[0] = {state, ways};
        for (int i = 0; i + d <= n; i += d) {
          if (i + r + d <= n) {
            add(pos[i + r], -1);
          }
          add(pos[i], 1);
          all[i / d + 1] = {state, ways};
        }
        std::sort(all.begin(), all.end());
        for (size_t i = 0; i < all.size(); ++i) {
          if (!i || all[i].first != all[i - 1].first) {
            ret += all[i].second;
          }
        }
      }
      ret %= mod;
    }
    printf("Case #%d: %lld\n", cas, ret);
  }
  return 0;
}

#include <cstdio>
#include <vector>

using i64 = long long;

const int mod = 1e9 + 7, inv2 = (mod + 1) / 2;
const int N = 2000 + 10;

int l[N], r[N], h[N];
i64 pw[N], ipw[N];

i64 pow_mod(i64 a, i64 n) {
  i64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

std::vector<i64> dfs(int u) {
  if (h[u] != -1) {
    return {pow_mod(2, h[u])};
  }
  auto a = dfs(l[u]);
  auto b = dfs(r[u]);
  h[u] = std::min(h[l[u]], h[r[u]]) - 1;
  std::vector<i64> ret(a.size() + b.size());
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < b.size(); ++j) {
      i64 w = a[i] * b[j] % mod * inv2 % mod * ipw[i + j + 1] % mod;
      i64 t = i64(h[u] + 1) * (i + j + 1);
      if (t < 0) continue;
      ret[i + j + 1] += w;
      ret[0] -= w * pow_mod(inv2, t) % mod;
    }
  }
  for (auto &x: ret) {
    x %= mod;
    x += mod;
    x %= mod;
  }
  return ret;
}

int main() {
  pw[0] = 1;
  for (int i = 1; i < N; ++i) {
    pw[i] = pw[i - 1] * 2 % mod;
    ipw[i] = pow_mod(pw[i] - 1, mod - 2);
  }
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int ty;
    scanf("%d", &ty);
    if (ty == 0) {
      scanf("%d%d", &l[i], &r[i]);
      --l[i], --r[i];
      h[i] = -1;
    } else {
      scanf("%d", &h[i]);
    }
  }
  auto dp = dfs(0);
  i64 ret = 0;
  for (auto &x: dp) ret += x;
  if (h[0] < 0) ret = 0;
  printf("%lld\n", ret % mod);
  return 0;
}

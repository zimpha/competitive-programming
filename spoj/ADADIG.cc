#include <cstdio>

using int64 = long long;

const int N = 3e5 + 10, mod = 1e9 + 7;

int fact[N], ifact[N], inv[N];
int n;

int64 dfs(int cnt, int rest, int sum, int last, int64 prod) {
  if (rest == 1) {
    return (int64)fact[cnt + n - sum] * ifact[n - sum] % mod * prod % mod;
  }
  int64 ret = 0;
  for (int i = last; i <= 9; ++i) if (rest % i == 0) {
    int t_rest = rest, e = 1;
    while (t_rest % i == 0 && sum + i * e <= n) {
      t_rest /= i;
      ret += dfs(cnt + e, t_rest, sum + i * e, i + 1, prod * ifact[e] % mod);
      ++e;
    }
  }
  return ret % mod;
}

void prepare() {
  fact[0] = fact[1] = 1;
  ifact[0] = ifact[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < N; ++i) {
    inv[i] = int64(mod - mod / i) * inv[mod % i] % mod;
    fact[i] = (int64)fact[i - 1] * i % mod;
    ifact[i] = (int64)ifact[i - 1] * inv[i] % mod;
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d", &n);
    printf("%lld\n", dfs(0, n, 0, 2, 1));
  }
  return 0;
}

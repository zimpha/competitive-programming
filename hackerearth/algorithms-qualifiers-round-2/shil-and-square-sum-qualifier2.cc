#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000000 + 10, MOD = 1e9 + 7;
int a[MAXN];

int main() {
  int n, k; scanf("%d%d", &n, &k);
  LL s(0), sj(0), sjj(0), p;
  for (int i = 0; i < k; ++ i) {
    int x; scanf("%d", &x);
    s += x; s %= MOD;
    int j = i + 1;
    sj += 1ll * j * x % MOD; sj %= MOD;
    sjj += 1ll * j * j % MOD * x % MOD; sjj %= MOD;
    a[i] = x;
  }
  printf("%lld", sjj);
  LL kk = 1ll * k * k % MOD;
  for (int i = k; i < n; ++ i) {
    int x; scanf("%d", &x);
    sjj -= 2 * sj - s; sjj %= MOD;
    sjj += kk * x % MOD; sjj %= MOD;
    if (sjj < 0) sjj += MOD;
    printf(" %lld", sjj);
    sj -= s; sj += 1ll * k * x % MOD;
    sj %= MOD; if (sj < 0) sj += MOD;
    s -= a[i - k]; s += x; s %= MOD;
    if (s < 0) s += MOD; a[i] = x;
  }
  puts("");
  return 0;
}

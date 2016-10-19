#include <bits/stdc++.h>

using LL = long long;

const int N = 10000001;

int mp[N], p[N], m;

void sieve() {
  m = 0;
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = i, p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}


int fac[100], cnt[100];
int M[N];

void dfs(int d, LL now, LL x) {
  if (now >= x - 1) return;
  if (d == m) {
    LL n = x * (x - 1) / now;
    assert(n > x);
    if (n < N) M[n] = x;
    return;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    dfs(d + 1, now, x);
    now *= fac[d];
  }
}

LL run(int n) {
  for (int i = 2; i <= n; ++i) M[i] = 1;
  for (int x = 2; x < n; ++x) {
    m = 0;
    for (int y = x; y != 1; y /= mp[y]) fac[m++] = mp[y];
    for (int y = x - 1; y != 1; y /= mp[y]) fac[m++] = mp[y];
    std::sort(fac, fac + m);
    int t = 0; cnt[0] = 1;
    for (int i = 1; i < m; ++i) {
      if (fac[i] == fac[i - 1]) ++cnt[t];
      else fac[++t] = fac[i], cnt[t] = 1;
    }
    m = t + 1;
    dfs(0, 1, x);
  }
  LL ret = 0;
  for (int i = 1; i <= n; ++i) ret += M[i];
  return ret;
}

int main() {
  sieve();
  std::cout << run(10000000) << std::endl;
  return 0;
}


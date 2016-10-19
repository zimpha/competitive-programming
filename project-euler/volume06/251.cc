#include <bits/stdc++.h>
using LL = long long;

const int N = 300000000;

int mp[N], p[N / 9], m;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = i, p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}

int fac[100], cnt[100];
int a, b, c, n;
LL S, upp;

int dfs(int d, LL now) {
  if (d == m) {
    return S / now + c * now * now + a <= n;
  }
  int ret = 0;
  for (int i = 0; i <= cnt[d]; ++i) {
    ret += dfs(d + 1, now);
    now *= fac[d];
    if (now > upp) break;
  }
  return ret;
}

// b^2c = (a + 1)^2 * (8a - 1) / 27
// a = 3x + 2 => b^2c = (x + 1)^2 * (8x + 5)
int run(int n) {
  ::n = n;
  int ret = 0;
  for (int x = 0; x * 3 + 2 <= n; ++x) {
    a = x * 3 + 2; m = 0;
    for (int b = x + 1; b > 1; b /= mp[b]) {
      fac[m++] = mp[b];
      fac[m++] = mp[b];
    }
    for (int b = x * 8 + 5; b > 1; b /= mp[b]) {
      fac[m++] = mp[b];
    }
    std::sort(fac, fac + m);
    int t = 0;
    cnt[0] = 1;
    for (int i = 1; i < m; ++i) {
      if (fac[i] == fac[i - 1]) cnt[t]++;
      else fac[++t] = fac[i], cnt[t] = 1;
    }
    m = t + 1; c = 1;
    S = 1;
    for (int i = 0; i < m; ++i) {
      if (cnt[i] & 1) c *= fac[i];
      cnt[i] = cnt[i] / 2;
      for (int j = 0; j < cnt[i]; ++j) S *= fac[i];
    }
    if (c > n - a) continue;
    upp = sqrt((n - a) / c) + 1;
    ret += dfs(0, 1);
  }
  return ret;
}

int main() {
  sieve();
  std::cout << run(1000) << std::endl;
  std::cout << run(110000000) << std::endl;
  return 0;
}

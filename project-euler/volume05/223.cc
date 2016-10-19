#include <bits/stdc++.h>

using PII = std::pair<int, int>;
using LL = long long;

const int N = 25000000;
int p[N], mp[N], m;

PII f[100];
int dfs(int a, LL x, int d) {
  if (d == m) {
    LL n = 1ll * (a - 1) * (a + 1);
    LL y = n / x;
    return y - x >= a * 2 && (x ^ y) % 2 == 0 && a + y <= N;
  }
  int ret = 0;
  for (int i = 0; i <= f[d].second; ++i) {
    ret += dfs(a, x, d + 1);
    x *= f[d].first;
  }
  return ret;
}

int run() {
  int ret = (N - 1) / 2;
  for (int a = 2; a * 3 <= N; ++a) {
    std::map<int, int> fac;
    for (int n = a - 1; n > 1; n /= mp[n]) fac[mp[n]]++;
    for (int n = a + 1; n > 1; n /= mp[n]) fac[mp[n]]++;
    m = 0;
    for (auto &&x: fac) f[m++] = x;
    ret += dfs(a, 1, 0);
  }
  return ret;
}

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

int main() {
  sieve();
  std::cout << run() << std::endl;
  return 0;
}

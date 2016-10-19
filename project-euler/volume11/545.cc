#include <bits/stdc++.h>

using LL = long long;
const int N = 10000000;

int p[N], mp[N], m;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = i, p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}

bool is_prime(LL n) {
  if (n < N) return mp[n] == n;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

bool check(LL n) {
  if (n % 2 == 0) return false;
  const int d[] = {2, 4, 14, 22, 28, 44, 154, 308};
  for (int i = 0; i < 8; ++i) {
    if (is_prime(n * d[i] + 1)) return false;
  }
  return true;
}

LL run(int n) {
  if (n == 1) return 308;
  std::vector<bool> vis(N, 0);
  for (int i = 2; i < N; ++i) if (!vis[i]) {
    if (!check(i)) {
      for (int j = i; j < N; j += i) vis[j] = 1;
    } else {
      if (--n == 1) return i * 308ll;
    }
  }
  return -1;
}

int main() {
  sieve();
  std::cout << run(10) << std::endl;
  std::cout << run(100000) << std::endl;
  return 0;
}

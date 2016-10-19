#include <bits/stdc++.h>

using LL = long long;

const int N = 10000000 + 10;
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

LL count(LL n) {
  LL ret = 0;
  for (LL a = 1, b = sqrt(n); a * a <= n; ++a) {
    while (a * a + b * b > n) --b;
    ret += b + 1;
  }
  return ret;
}

int mu(int n) {
  if (n == 1) return 1;
  if (n % 4 == 0) return 0;
  std::map<int, int> cnt;
  while (n > 1) {
    cnt[mp[n]]++;
    n /= mp[n];
  }
  int ret = 1;
  for (auto &&x: cnt) {
    if (x.second > 2) return 0;
    if (x.first == 2) ret *= -1;
    else if (x.first % 4 == 3) {
      if (x.second == 2) ret *= -1;
      else return 0;
    } else {
      if (x.second == 1) ret *= -2;
      else ret *= 1;
    }
  }
  return ret;
}

LL run(LL n) {
  LL ret = 0, m = sqrt(n);
  for (LL z = 1; z * z <= n; ++z) {
    ret += mu(z) * count(n / z / z);
  }
  return ret;
}

int main() {
  sieve();
  std::cout << run(10) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(10000) << std::endl;
  std::cout << run(100000000) << std::endl;
  std::cout << run(100000000000000ll) << std::endl;
}

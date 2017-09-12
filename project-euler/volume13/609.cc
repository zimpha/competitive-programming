#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

const int mod = 1e9 + 7;

using int64 = long long;

int64 P(int n) {
  std::vector<int> pi(n + 1), p;
  for (int i = 2; i <= n; ++i) {
    if (!pi[i]) p.push_back(i);
    for (int j = 0, u = n / i; j < p.size() && p[j] <= u; ++j) {
      pi[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
  for (int i = 2; i <= n; ++i) {
    pi[i] = !pi[i] + pi[i - 1];
  }
  std::vector<int> cnt(20);
  for (int i = 1; i <= n; ++i) {
    int s = 0;
    for (int u = i; u; u = pi[u]) {
      s += pi[u] == pi[u - 1];
      if (u != i) cnt[s]++;
    }
  }
  int64 ret = 1;
  for (auto &&x: cnt){
    if (x) ret = ret * x % mod;
  }
  return ret;
}

int main() {
  std::cout << P(10) << std::endl;
  std::cout << P(100) << std::endl;
  std::cout << P(100000000) << std::endl;
  return 0;
}

#include <bits/stdc++.h>

const int M = 1000000123;
const int N = 100000;

long fac[N], inv[N], dp[N];

long pm(long a, long n) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % M;
    a = a * a % M;
  }
  return r;
}

long P(int k, int r, int n) {
  std::vector<int> seg;
  for (int i = k; i <= n; i += k) {
    seg.push_back(k);
  }
  if (n % k) seg.push_back(n % k);
  for (size_t i = 0; i <= seg.size(); ++i) dp[i] = 0;
  dp[0] = fac[n];
  for (size_t i = 0; i < seg.size(); ++i) {
    int len = 0;
    dp[i] = (dp[i] % M + M) % M;
    for (size_t j = i; j < seg.size(); ++j) {
      len += seg[j];
      long val = dp[i] * inv[len] % M;
      if ((j - i) & 1) val = M - val;
      dp[j + 1] += val;
    }
  }
  return dp[seg.size()];
}


long run(int r, int n) {
  fac[0] = inv[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = pm(i, r) * fac[i - 1] % M;
    inv[i] = pm(fac[i], M - 2) % M;
  }
  long ret = 0;
  for (int k = 1; k <= n; ++k) {
    ret += P(k, r, n);
  }
  return ret %= M;
}

int main() {
  std::cout << run(5, 5) << std::endl;
  std::cout << run(50, 50) << std::endl;
  std::cout << run(50000, 50000) << std::endl;
  return 0;
}

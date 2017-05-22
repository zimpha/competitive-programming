#include <bits/stdc++.h>

const int n = 12;
const int N = n * (n + 1) / 2 / 2;
const int mod = 1e9 + 7;
int dp[N + 1][n / 2 + 1];

inline void add_mod(int &x, int y) {
  x += y;
  if (x >= mod) x -= mod;
}

int main() {
  int a[100], now = 0;
  for (int i = 0; i < n; ++i) a[i] = i + 1;
  do {
    int s = 0;
    for (int i = 0; i < n; ++i) {
      if (i & 1) s -= a[i];
      else s += a[i];
    }
    now += s == 0;
  } while (std::next_permutation(a, a + n));
  std::cout << now << std::endl;
  dp[0][0] = 1;
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += i;
    sum = std::min(sum, N);
    //std::cout << i << std::endl;
    int t = std::min(n / 2, i);
    for (int j = sum; j >= i; --j) {
      for (int k = t; k >= 1; --k) {
        add_mod(dp[j][k], dp[j - i][k - 1]);
      }
    }
  }
  long ret = dp[N][n / 2];
  std::cout << ret << std::endl;
  for (int i = 1; i <= n / 2; ++i) {
    ret = ret * i % mod * i % mod;
  }
  std::cout << ret << std::endl;
  return 0;
}

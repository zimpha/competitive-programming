#include <bits/stdc++.h>

long cnt(long n, long p) {
  long ret = 0;
  for (long pw = p; pw <= n; pw *= p) {
    ret += n / pw;
    if (pw > n / p) break;
  }
  return ret;
}

long run(int n) {
  std::vector<bool> mark(n + 1, 0);
  std::vector<int> pl;
  std::vector<long> N(n + 1, 0);
  for (int i = 2; i <= n; ++i) {
    if (mark[i]) continue;
    pl.push_back(i);
    for (int j = i; j <= n; j += i) mark[j] = 1;
  }
  typedef std::pair<int, long> ev_t;
  for (auto &&p: pl) {
    long left = 0, right = 0;
    for (int i = p; i <= n; i += p) {
      long c = cnt(i, p) * 1234567890;
      right = c * p;
      while (left < right) {
        long mid = (left + right - 1) >> 1;
        if (cnt(mid, p) >= c) right = mid;
        else left = mid + 1;
      }
      N[i] = std::max(N[i], left);
    }
  }
  long ret = 0;
  for (int i = 1; i <= n; ++i) {
    N[i] = std::max(N[i], N[i - 1]);
    if (i >= 10) ret += N[i];
    ret %= 1000000000000000000ll;
  }
  return ret;
}

int main() {
  std::cout << run(1000) << std::endl;
  std::cout << run(100000) << std::endl;
  std::cout << run(1000000) << std::endl;
  return 0;
}


#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

void run(int x) {
  const int n = 1000000;
  std::vector<bool> mark(n);
  std::vector<int> ps;
  for (int i = 2; i < n; ++i) {
    if (!mark[i]) ps.push_back(i);
    for (int j = i; j < n; j += i) {
      mark[j] = true;
    }
  }
  std::vector<int64> mu(n), d(n);
  int64 a = -1, b = -1, sum = 0;
  for (int64 i = 0; ; ++i) {
    int64 l = i * n, r = l + n - 1;
    for (int64 j = l; j <= r; ++j) {
      d[j - l] = j;
      mu[j - l] = 1;
    }
    for (auto &&p: ps) {
      int64 x = (l + p - 1) / p * p;
      if (x == 0) x += p;
      for (; x <= r; x += p) {
        int c = 0;
        while (d[x - l] % p == 0) ++c, d[x - l] /= p;
        if (c == 1) mu[x - l] *= -1;
        else mu[x - l] = 0;
      }
    }
    for (int64 j = l; j <= r; ++j) {
      if (d[j - l] > 1) mu[j - l] *= -1;
    }
    if (l == 0) mu[0] = 0;
    for (int64 j = l; j <= r; ++j) {
      sum += mu[j - l];
      if (sum == -x && a == -1) a = j;
      if (sum == +x && b == -1) b = j;
      if (a != -1 && b != -1) break;
    }
    if (a != -1 && b != -1) break;
  }
  printf("%lld,%lld\n", a, b);
}

int main() {
  run(1234);
  run(9876);
  return 0;
}

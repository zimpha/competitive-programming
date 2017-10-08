#include <cstdio>
#include <cmath>
#include <algorithm>

using int64 = long long;

const int N = 2e5;

int64 ssum[N][4], lsum[N][4];
int p[N], pc;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!p[i]) p[pc++] = i;
    for (int j = 0; j < pc && p[j] * i < N; ++j) {
      p[i * p[j]] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

int64 prime_count(int64 n) {
  const int64 v = static_cast<int64>(sqrt(n));
  for (int i = 1; i <= v; ++i) {
    for (int j = 0; j < 4 && j <= i; ++j) {
      ssum[i][j] = (i - j) / 4 + 1;
      lsum[i][j] = (n / i - j) / 4 + 1;
    }
    --ssum[i][0], --lsum[i][0];
  }
  for (int it = 0; it < pc && ::p[it] <= v; ++it) {
    int64 p = ::p[it], q = p * p, ed = std::min(v, n / q);
    int m = p % 4;
    for (int i = 1; i <= ed; ++i) {
      int64 d = i * p;
      if (d <= v) {
        for (int j = 0; j < 4; ++j) {
          lsum[i][j * m % 4] -= lsum[d][j] - ssum[p - 1][j];
        }
      } else {
        for (int j = 0; j < 4; ++j) {
          lsum[i][j * m % 4] -= ssum[n / d][j] - ssum[p - 1][j];
        }
      }
    }
    for (int64 i = v; i >= q; --i) {
      for (int j = 0; j < 4; ++j) {
        ssum[i][j * m % 4] -= ssum[i / p][j] - ssum[p - 1][j];
      }
    }
  }
  return lsum[1][1] - 1;
}

int main() {
  sieve();
  int64 n;
  scanf("%lld", &n);
  printf("%lld\n", prime_count(n));
  return 0;
}

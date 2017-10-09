#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5, M = 12;

int64 ssum[N][M], lsum[N][M];
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

void prime_count(int64 n, int64 mod) {
  const int64 v = static_cast<int64>(sqrt(n));
  for (int i = 1; i <= v; ++i) {
    for (int j = 0; j < mod; ++j) {
      ssum[i][j] = (i >= j) ? (i - j) / mod + 1 : 0;
      lsum[i][j] = (n / i >= j) ? (n / i - j) / mod + 1 : 0;
    }
    --ssum[i][0], --lsum[i][0];
    --ssum[i][1], --lsum[i][1];
  }
  std::vector<bool> mark(v + 1);
  for (int it = 0; it < pc && ::p[it] <= v; ++it) {
    int64 p = ::p[it], q = p * p, ed = std::min(v, n / q);
    int delta = (p & 1) + 1;
    for (int i = 1; i <= ed; i += delta) if (!mark[i]) {
      int64 d = i * p;
      if (d <= v) {
        for (int j = 0; j < mod; ++j) {
          lsum[i][p * j % mod] -= lsum[d][j] - ssum[p - 1][j];
        }
      } else {
        for (int j = 0; j < mod; ++j) {
          lsum[i][p * j % mod] -= ssum[n / d][j] - ssum[p - 1][j];
        }
      }
    }
    for (int64 i = q; i <= ed; i += p * delta) mark[i] = true;
    for (int64 i = v; i >= q; --i) {
      for (int j = 0; j < mod; ++j) {
        ssum[i][p * j % mod] -= ssum[i / p][j] - ssum[p - 1][j];
      }
    }
  }
  for (int i = 0; i < mod; ++i) {
    printf("%lld\n", lsum[1][i]);
  }
}

int main() {
  sieve();
  int64 n, m;
  scanf("%lld%lld", &n, &m);
  prime_count(n, m);
  return 0;
}

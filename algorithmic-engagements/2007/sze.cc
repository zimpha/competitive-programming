#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using uint64 = unsigned long long;

const int N = 1000 + 10, mod = 1e9 + 7;
const int inv = 41666667;
const uint64 seed = 1e9 + 7;

int a[N][N], b[N][N];
bool c[N][N];

uint64 pow_mod(uint64 a, uint64 n) {
  uint64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[i][j]);
      m += a[i][j] == 0;
      c[i][j] = a[i][j];
    }
  }
  std::vector<uint64> candidate;
  for (int it = 0; it < 4; ++it) {
    uint64 hash = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        b[j][n - 1 - i] = a[i][j];
        hash = hash * seed + a[i][j] + '0';
      }
    }
    candidate.push_back(hash);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        a[i][j] = b[i][j];
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      a[i][j] = i * n + j;
    }
  }
  int ret = 0, cnt = 0;
  for (int it = 0; it < 4; ++it) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        b[j][n - 1 - i] = a[i][j];
      }
    }
    if (candidate[it] == candidate[0]) {
      std::vector<std::vector<bool>> mark(n, std::vector<bool>(n));
      int cyc = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) if (c[i][j] == 0 && !mark[i][j]) {
          for (int x = i, y = j; !mark[x][y]; ) {
            int u = a[x][y];
            mark[x][y] = 1;
            x = u / n;
            y = u % n;
          }
          ++cyc;
        }
      }
      ret += pow_mod(2, cyc);
      ret %= mod;
      ++cnt;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        a[i][j] = b[i][j];
      }
    }
  }
  ret = ret * pow_mod(cnt, mod - 2) % mod;
  cnt = 1;
  for (int i = 1; i <= 6; ++i) {
    cnt = (uint64)cnt * (ret + 6 - i) % mod;
    cnt = cnt * pow_mod(i, mod - 2) % mod;
  }
  printf("%d\n", (int)cnt);
  return 0;
}

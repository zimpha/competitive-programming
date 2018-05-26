#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>

using uint = unsigned int;
using uint64 = unsigned long long;

const int N = 4100, M = 300, seed = 1e9 + 7;

uint64 hash[N][4], pw[N];
int map[256], cnt[65536];
uint s[N][M];
short a[N][N];

int main() {
  srand(time(0));
  for (int mask = 0; mask < 65536; ++mask) {
    for (int i = 0, m = mask; i < 8; ++i) {
      cnt[mask] += !!(m & 3);
      m >>= 2;
    }
  }
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  map['A'] = 0;
  map['C'] = 1;
  map['G'] = 2;
  map['T'] = 3;
  pw[0] = 1;
  for (int i = 0; i < n; ++i) {
    pw[i + 1] = pw[i] * seed;
    static char buf[N + 10];
    scanf("%s", buf);
    for (int j = 0; j < m; j += 16) {
      uint v = 0;
      for (int x = 0; x + j < m && x < 16; ++x) {
        v = v << 2 | map[buf[x + j]];
      }
      s[i][j / 16] = v;
    }
    for (int j = 0; j < m; ++j) {
      a[i][j] = map[buf[j]];
      hash[j][a[i][j]] += pw[i];
    }
  }
  std::vector<int> candidate;
  for (int i = 0; i < n; ++i) {
    uint64 all = 0, now = 0;
    for (int j = 0; j < n; ++j) {
      if (i != j) all += pw[j] * k;
    }
    for (int j = 0; j < m; ++j) {
      for (int k = 0; k < 4; ++k) {
        if (k != a[i][j]) now += hash[j][k];
      }
    }
    if (now == all) candidate.push_back(i);
  }
  m = (m + 15) / 16;
  for (auto &&x: candidate) {
    int count = 0;
    for (int i = 0; i < n; ++i) if (i != x) {
      int diff = 0;
      for (int j = 0; j < m; ++j) {
        uint u = s[x][j] ^ s[i][j];
        diff += cnt[u >> 16] + cnt[u & 65535];
      }
      count += diff == k;
    }
    if (count == n - 1) {
      printf("%d\n", x + 1);
      return 0;
    }
  }
  return 0;
}

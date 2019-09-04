#include <cstdio>
#include <vector>
#include <bitset>

const int N = 320, M = 1e5 + 10;
using uint32 = unsigned int;

uint32 bs[M][N / 32];
int popcount[1 << 16];

int main() {
  for (int i = 1; i < (1 << 16); ++i) {
    popcount[i] = popcount[i ^ (i & -i)] + 1;
  }
  int n;
  scanf("%d", &n);
  std::vector<std::vector<int>> a(n);
  for (int i = 0, l; i < n; ++i) {
    scanf("%d", &l);
    for (int j = 0, x; j < l; ++j) {
      scanf("%d", &x);
      a[i].emplace_back(x);
      bs[x][i / 32] ^= uint32(1) << (i % 32);
    }
  }
  int m = (n + 31) / 32;
  for (auto &s: a) {
    int sum = 0;
    for (auto &x: s) for (auto &y: s) if (x < y) {
      int cu = 0, cv = 0, cw = 0;
      for (int i = 0; i < m; ++i) {
        uint32 u = ~bs[x][i] & bs[y][i];
        uint32 v = ~bs[y][i] & bs[x][i];
        uint32 w = u & v;
        cu += popcount[u >> 16] + popcount[u % 65536];
        cv += popcount[v >> 16] + popcount[v % 65536];
        cw += popcount[w >> 16] + popcount[w % 65536];
      }
      sum += cu * cv - cw * cw;
    }
    printf("%d\n", sum);
  }
  return 0;
}

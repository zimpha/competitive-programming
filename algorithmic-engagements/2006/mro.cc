#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>

using int24 = long long;

int n, mod;

void mul(int24 a[24][24], int24 b[24][24]) {
  static int24 c[24][24];
  for (int i = 0; i < 24; ++i) {
    for (int j = 0; j < 24; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < 24; ++k) {
        c[i][j] += a[i][k] * b[k][j] % mod;
      }
      c[i][j] %= mod;
    }
  }
  memcpy(a, c, sizeof(c));
}

std::vector<std::vector<int>> go = {
  {1, 3, 4},
  {0, 2, 5},
  {1, 3, 6},
  {0, 2, 7},
  {0, 5, 7},
  {1, 4, 6},
  {2, 5, 7},
  {3, 4, 6},
};

int main() {
  char s[10], t[10];
  scanf("%s%s", s, t);
  scanf("%d%d", &n, &mod);
  int24 ret[24];
  int24 trans[24][24];
  memset(trans, 0, sizeof(trans));
  memset(ret, 0, sizeof(ret));
  std::map<int, int> mp;
  int size = 0;
  for (int u = 0; u < 8; ++u) {
    for (auto &v: go[u]) {
      mp[u * 8 + v] = size++;
    }
  }
  int src = s[0] - 'A';
  int dst = t[0] - 'A';
  for (auto &x: go[src]) {
    ret[mp[src * 8 + x]] = 1;
  }
  for (int x = 0; x < 8; ++x) {
    for (auto &y: go[x]) for (auto &z: go[y]) {
      if (x == z) continue;
      trans[mp[x * 8 + y]][mp[y * 8 + z]] = 1;
    }
  }
  --n;
  for (; n; n >>= 1) {
    if (n & 1) {
      static int24 tmp[24];
      memset(tmp, 0, sizeof(tmp));
      for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 24; ++j) {
          tmp[j] += ret[i] * trans[i][j] % mod;
        }
      }
      for (int i = 0; i < 24; ++i) {
        ret[i] = tmp[i] % mod;
      }
    }
    mul(trans, trans);
  }
  int24 cnt = 0;
  for (int u = 0; u < 8; ++u) {
    for (auto &v: go[u]) if (v == dst) {
      cnt += ret[mp[u * 8 + v]];
    }
  }
  printf("%lld\n", cnt % mod);
  return 0;
}

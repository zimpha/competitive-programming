#include <cstdio>
#include <bitset>
#include <vector>
#include <algorithm>

using state = std::bitset<250>;

int det_mod(int n, std::vector<state>& a) {
  for (int i = 0, s; i < n; ++i) {
    for (s = i; s < n; ++s) {
      if (a[s][i]) break;
    }
    if (s == n) return 0;
    if (s != i) {
      std::swap(a[s], a[i]);
    }
    for (int j = i + 1; j < n; ++j) if (a[j][i]) {
      a[j] ^= a[i];
    }
  }
  return 1;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<state> a(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0, x; j < n; ++j) {
        scanf("%d", &x);
        a[i][j] = x;
      }
    }
    printf("%d\n", det_mod(n, a));
  }
  return 0;
}

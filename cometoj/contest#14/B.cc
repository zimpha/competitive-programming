#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>

const int N = 1e6 + 10;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  int sn = 0;
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d%s", &n, s);
    assert(4 <= n && n <= 1000000);
    assert(strlen(s) == n);
    sn += n;
    assert(sn <= 1000000);
    int ret = -1;
    int p = -1, pi = -1, pin = -1;
    for (int i = 0; i < n; ++i) {
      if (s[i] == 'p') if (p == -1) p = i;
      if (s[i] == 'i') if (p != -1 && pi == -1) pi = i;
      if (s[i] == 'n') if (pi != -1 && pin == -1) pin = i;
    }
    int k = -1, nk = -1, ink = -1;
    for (int i = n - 1; i >= 0; --i) {
      if (s[i] == 'k') if (k == -1) k = i;
      if (s[i] == 'n') if (k != -1 && nk == -1) nk = i;
      if (s[i] == 'i') if (nk != -1 && ink == -1) ink = i;
    }
    if (p != -1 && ink != -1 && p < ink) ret = std::max(ret, ink - p - 1);
    if (pi != -1 && nk != -1 && pi < nk) ret = std::max(ret, nk - pi - 1);
    if (pin != -1 && k != -1 && pin < k) ret = std::max(ret, k - pin - 1);
    printf("%d\n", ret);
  }
  return 0;
}

#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 1000000 + 10;

char s[N * 2];
int nine[N], zero[N];

std::vector<int> ext_kmp(char *s, int n) {
  std::vector<int> z(n, 0);
  for (int i = 1, x = 0, y = 0; i < n; ++i) {
    if (i <= y) z[i] = std::min(y - i, z[i - x]);
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
    if (y <= i + z[i]) x = i, y = i + z[i];
  }
  z[0] = n;
  return z;
}

int main() {
  while (scanf("%s", s) == 1) {
    int n = strlen(s);
    std::reverse(s, s + n);
    nine[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
      s[i] -= '0';
      if (s[i] == 9) nine[i] = nine[i + 1] + 1;
      else nine[i] = 0;
    }
    zero[0] = s[0] == 0;
    for (int i = 1; i < n; ++i) {
      if (s[i] == 0) zero[i] = zero[i - 1] + 1;
      else zero[i] = 0;
    }
    int now = 0, next = 0;
    for (int i = 0; i < n; ++i) {
      s[i + n] = s[i];
      if (now < s[i]) now += 10, next -= 1;
      s[i] = now - s[i];
      now = next, next = 0;
    }
    int ret = 0;
    auto z = ext_kmp(s, n * 2);
    for (int i = 1; i < n; ++i) {
      if (zero[i - 1] == i) {
        ret = i - 1;
        continue;
      }
      int lcp = std::min(i, z[i + n]);
      ret = std::max(ret, lcp);
      if (lcp == n - i) {
        ret = std::max(ret, lcp + std::min(nine[lcp], i - lcp));
      }
      if (lcp == i) {
        ret = std::max(ret, lcp + nine[i + lcp]);
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

const int N = 1e6 + 10;

char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  auto x = ext_kmp(s, n);
  std::reverse(s, s + n);
  auto y = ext_kmp(s, n);
  long long ret = 0;
  for (int i = 3; i + 1 < n; ++i) if (n - i < i){
    auto u = std::min(x[i], n - i);
    auto v = std::min(y[n - i], n - i);
    int l = std::max(1, n - i - v);
    int r = std::min(u, n - i - 1);
    ret += std::max(0, r - l + 1);
  }
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int N = 1e6 + 10;

char s[N];

int main() {
  scanf("%s", s);
  int n = strlen(s);
  std::reverse(s, s + n);
  std::vector<int> f(n), g(n);
  for (int i = 0; i < n; ++i) {
    int o = s[i] - '0';
    if (i == 0) f[i] = o, g[i] = 11 - o;
    else {
      f[i] = std::min(f[i - 1], g[i - 1]) + o;
      g[i] = std::min(f[i - 1] + 11 - o, g[i - 1] + 9 - o);
    }
  }
  printf("%d\n", std::min(f.back(), g.back()));
  return 0;
}

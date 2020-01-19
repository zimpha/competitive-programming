#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e5 + 10;

char s[N], t[N];

int main() {
  int n, q;
  scanf("%s%d", s, &q);
  n = strlen(s);
  std::vector<std::vector<int>> str(n);
  for (int i = 0; i < q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    str[x - 1].push_back(y - 1);
  }
  std::vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
  }
  int l = 1, r = n + 1;
  while (l < r) {
    int m = (l + r - 1) >> 1;
    int last[26];
    std::vector<bool> mark(n);
    std::vector<int> next(n + 1, n);
    bool valid = true;
    for (int i = 0; i < m - 1; ++i) mark[p[i] - 1] = 1;
    for (int i = 0; i < 26; ++i) last[i] = n;
    for (int i = n - 1; i >= 0 && valid; --i) {
      if (!mark[i]) next[i] = last[s[i] - 'a'];
      if (!mark[i]) last[s[i] - 'a'] = i;
      for (auto &j : str[i]) {
        for (int k = 0; k < 26 && valid; ++k) {
          int x = last[k], y = next[x];
          if (x <= j && y <= j) valid = false;
        }
        if (!valid) break;
      }
    }
    if (valid) r = m;
    else l = m + 1;
  }
  printf("%d\n", l - 1);
  return 0;
}

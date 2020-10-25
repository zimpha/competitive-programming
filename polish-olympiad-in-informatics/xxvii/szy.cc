#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1e6 + 10;

char s[N], t[N];
std::vector<int> pos[256];
int fail[N];

int next(int i, int c) {
  auto it = std::lower_bound(pos[c].begin(), pos[c].end(), i);
  if (it == pos[c].end()) return -1;
  else return *it;
}

int main() {
  scanf("%s%s", s, t);
  int n = strlen(s);
  int m = strlen(t);
  fail[0] = -1;
  for (int i = 1, j = -1; i < n; ++i) {
    while (j >= 0 && s[j + 1] != s[i]) j = fail[j];
    fail[i] = (s[j + 1] == s[i] ? ++j : j);
  }
  int border = fail[n - 1] + 1;

  for (int i = 0; i < n; ++i) {
    pos[s[i]].push_back(i);
  }

  int start = 0, ret = 0;
  for (int i = 0; i < m && ret != -1; ++i) {
    int p = next(start, t[i]);
    if (p == -1) {
      ++ret;
      p = next(border, t[i]);
      if (p == -1) ret = -1;
    }
    start = p + 1;
  }
  if (ret == -1) puts("INF");
  else printf("%d\n", ret);
  return 0;
}

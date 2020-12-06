#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 4000 + 10;

char s[N], t[N];
int seg[N];

int solve(char *s, char *t, int k) {
  int n = strlen(s);
  int m = strlen(t);
  int ret = 0;
  for (int offset = 0; offset < m; ++offset) {
    int ns = 0, bound = std::min(n, m - offset), cnt = 0;
    for (int i = 0; i < bound; ++i) {
      if (s[i] == t[i + offset]) ++cnt;
      else {
        seg[ns++] = cnt;
        cnt = 0;
      }
    }
    seg[ns++] = cnt;
    for (int i = ns - 1; i >= 0; --i) seg[i] += seg[i + 1];
    for (int i = 0; i < ns; ++i) {
      int j = std::min(i + k + 1, ns);
      ret = std::max(ret, seg[i] - seg[j] + j - i - 1);
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    scanf("%s%s", s, t);
    printf("%d\n", std::max(solve(s, t, k), solve(t, s, k)));
  }
  return 0;
}

#include <cstdio>

const int N = 510;

char a[N][N], s[N];
int up[N][N][26];

int main() {
  int n, m, o;
  scanf("%d%d%d", &n, &m, &o);
  for (int i = 0; i < n; ++i) scanf("%s", a[i]);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int o = 0; o < 26; ++o) {
        int l = 0;
        while (l <= n && a[(i - l + n) % n][j] != o + 'a') ++l;
        if (l > n) l = 1e8;
        up[i][j][o] = l;
      }
    }
  }
  scanf("%s", s);
  int ret = 1e8;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j + o <= m; ++j) {
      int cnt = 0;
      for (int k = 0; k < o; ++k) {
        cnt += up[i][j + k][s[k] - 'a'];
      }
      if (cnt < ret) ret = cnt;
    }
  }
  if (ret == 1e8) puts("-1");
  else printf("%d\n", ret);
  return 0;
}

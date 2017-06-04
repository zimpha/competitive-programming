#include <cstdio>
#include <cstring>

const int N = 100 + 10, M = 10;

char s[N];
char t[M][N];
int n, m;

bool dfs(int d, int p) {
  if (d == m) {
    if (p == n) {
      bool flag = true;
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
          if (strcmp(t[i], t[j]) == 0) flag = false;
        }
      }
      if (flag) {
        puts("YES");
        for (int i = 0; i < m; ++i) puts(t[i]);
      }
      return flag;
    }
    return false;
  }
  for (int l = 1; p + l <= n; ++l) {
    t[d][l - 1] = s[p + l - 1];
    t[d][l] = 0;
    if (dfs(d + 1, p + l)) return true;
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%d", s, &m);
    n = strlen(s);
    if (n >= (1 + m) * m / 2) {
      puts("YES");
      for (int i = 1; i <= m; ++i) {
        int l = i * (i - 1) / 2, r = i == m ? n : i * (i + 1) / 2;
        for (int j = l; j < r; ++j) putchar(s[j]);
        puts("");
      }
    } else {
      if (!dfs(0, 0)) puts("NO");
    }
  }
  return 0;
}

#include <cstdio>
#include <algorithm>

const int N = 200;

int s[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        scanf("%d", &s[i][j]);
      }
    }
    int mx = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0, k; j < m; j = k) {
        for (k = j; k < m && s[i][j] == s[i][k]; ++k);
        if (s[i][j] == 1) mx = std::max(mx, k - j);
      }
    }
    for (int j = 0; j < m; ++j) {
      for (int i = 0, k; i < n; i = k) {
        for (k = i; k < n && s[i][j] == s[k][j]; ++k);
        if (s[i][j] == 1) mx = std::max(mx, k - i);
      }
    }
    if (mx > k) {
      puts("NO");
      continue;
    }
    puts("YES");
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (s[i][j] == 1) s[i][j] = (i + j) % k + 1;
        printf("%d ", s[i][j]);
      }
      puts("");
    }
  }
  return 0;
}

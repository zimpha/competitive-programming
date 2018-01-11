#include <cstdio>
#include <vector>

const int N = 1e3 + 10, S = 1e4;

std::vector<int> d[S + 1];
int s[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", &s[i][j]);
      s[i][j] = s[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    }
  }
  for (int i = 1; i <= S; ++i) {
    for (int j = i; j <= S; j += i) {
      d[j].push_back(i);
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1, area; cas <= T; ++cas) {
    scanf("%d", &area);
    int ret = -1e9;
    for (auto &&x: d[area]) {
      if (x > n || area / x > m) continue;
      int y = area / x;
      for (int i = x; i <= n; ++i) {
        for (int j = y; j <= m; ++j) {
          ret = std::max(ret, s[i][j] - s[i - x][j] - s[i][j - y] + s[i - x][j - y]);
        }
      }
    }
    if (ret == -1e9) ret = -1;
    printf("%d\n", ret);
  }
  return 0;
}

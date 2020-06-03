#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

const int N = 4000 + 10;

int dsu[N];
int dp[N][N];
int from[N][N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) dsu[i] = i;
    for (int i = 0; i < m; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x, --y;
      for (int j = 0; j <= y - x; ++j) {
        int u = get(x + j);
        int v = get(y - j);
        if (u != v) dsu[u] = v;
      }
    }
    std::vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
      cnt[get(i)]++;
    }
    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < n; ++i) if (cnt[i]) {
      a.emplace_back(cnt[i], i);
    }
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= n; ++j) {
        dp[i][j] = 0;
        from[i][j] = -1;
      }
    }
    dp[0][0] = 1;
    m = a.size();
    for (int i = 1; i <= m; ++i) {
      for (int j = 0; j <= n; ++j) {
        dp[i][j] = dp[i - 1][j];
        from[i][j] = j;
        if (j >= a[i - 1].first && dp[i - 1][j - a[i - 1].first]) {
          dp[i][j] = 1;
          from[i][j] = j - a[i - 1].first;
        }
      }
    }
    int best = -1;
    for (int i = 0; i <= n; ++i) {
      if (dp[m][i] && std::abs(n - i * 2) < std::abs(n - best * 2)) best = i;
    }
    std::vector<int> col(n);
    for (int i = m, j = best; i > 0; --i) {
      if (from[i][j] == j) col[a[i - 1].second] = 0;
      else col[a[i - 1].second] = 1;
      j = from[i][j];
    }
    std::string s(n, '0');
    for (int i = 0; i < n; ++i) {
      s[i] = col[get(i)] + '0';
    }
    printf("Case #%d: %s\n", cas, s.c_str());
    //fprintf(stderr, "diff %d\n", std::abs(n - best * 2));
  }
  return 0;
}

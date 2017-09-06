#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

const int N = 62;

int dp[N][N][N * N], prev[N][N][N * N];

void build(std::vector<int> d) {
  int n = d.size();
  std::vector<std::string> g(n, std::string(n, '0'));
  std::vector<std::pair<int, int>> score(n);
  for (int i = 0; i < n; ++i) {
    score[i] = {d[i], i};
  }
  for (int i = 0; i < n; ++i) {
    std::sort(score.begin() + i, score.end());
    int win = score[i].first;
    int u = score[i].second;
    for (int j = i + 1; j < n; ++j) {
      int v = score[j].second;
      if (j - i <= win) {
        g[u][v] = '1';
        g[v][u] = '0';
      } else {
        g[u][v] = '0';
        g[v][u] = '1';
        score[j].first--;
      }
    }
  }
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    printf("%s\n", g[i].c_str());
  }
}

int main() {
  int m;
  scanf("%d", &m);
  std::vector<int> a(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &a[i]);
  }
  memset(prev, -1, sizeof(prev));
  std::sort(a.begin(), a.end());
  dp[1][0][a[0]] = 1;
  for (int i = 1; i < N; ++i) {
    int expected = (i + 1) * i / 2;
    for (int j = 0; j < m; ++j) {
      for (int k = 0; k < N * N; ++k) {
        if (!dp[i][j][k]) continue;
        if (k + a[j] < N * N && k + a[j] >= expected) {
          dp[i + 1][j][k + a[j]] = 1;
          prev[i + 1][j][k + a[j]] = j;
        }
        if (j + 1 < m && k + a[j + 1] < N * N && k + a[j + 1] >= expected) {
          dp[i + 1][j + 1][k + a[j + 1]] = 1;
          prev[i + 1][j + 1][k + a[j + 1]] = j;
        }
      }
    }
  }
  int n = -1;
  for (int i = m; i < N; ++i) {
    if (dp[i][m - 1][i * (i - 1) / 2]) {
      n = i;
      break;
    }
  }
  if (n == -1) {
    puts("=");
    return 0;
  }
  std::vector<int> d(n);
  for (int i = n, j = m - 1, s = n * (n - 1) / 2; i; ) {
    d[i - 1] = a[j];
    j = prev[i][j][s];
    s -= d[--i];
  }
  build(d);
  return 0;
}
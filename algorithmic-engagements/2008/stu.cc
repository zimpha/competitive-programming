#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 300;
const int64 inf = 1e18;

int64 w[N][N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      w[i][j] = -inf;
    }
  }
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    w[a - 1][b - 1] = c;
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) if (i != k && w[i][k] != -inf) {
      for (int j = 0; j < n; ++j) if (j != k && w[k][j] != -inf) {
        w[i][j] = std::max(w[i][j], w[i][k] + w[k][j]);
      }
    }
  }
  std::vector<int> mark(n);
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      if (w[i][k] != -inf && w[k][i] != -inf) {
        if (w[i][k] + w[k][i] > w[i][i]) mark[i] = 1;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      mark[i] |= w[i][j] != -inf && w[j][i] != -inf && mark[j];
    }
  }
  std::vector<int> ret;
  for (int i = 0; i < n; ++i) {
    if (mark[i]) ret.push_back(i);
  }
  printf("%d\n", (int)ret.size());
  for (auto &x: ret) printf("%d ", x + 1);
  puts("");
  return 0;
}

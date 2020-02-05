#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 310;
const int mod = 1e9 + 7;

std::vector<int> pos[N][N * 2];
int a[N][N];
int n, m, k;

bool fill_row(std::vector<int> &row, const std::vector<int> &col, int r, int c) {
  for (; r < n; ++r) if (a[r][c] != col[c]) {
    if (row[r] == -1) row[r] = a[r][c];
    else {
      if (row[r] != a[r][c]) return false;
    }
  }
  return true;
}

int64 dfs(int r, const std::vector<int>& row, const std::vector<int>& col, std::vector<int>& ways) {
  auto mi = *std::min_element(col.begin(), col.end());
  // all columns are fixed
  if (mi != -1 || r == n) {
    int64 ret = 1;
    for (int i = 0; i < r; ++i) {
      ret = ret * ways[i] % mod;
    }
    for (int i = r; i < n; ++i) {
      ret = ret * (row[i] == -1 ? k : 1) % mod;
    }
    for (int i = 0; i < m; ++i) {
      if (col[i] == -1) ret = ret * k % mod;
    }
    return ret;
  }
  if (row[r] != -1) {
    std::vector<int> t_row(row), t_col(col);
    for (int c = 0; c < m; ++c) if (t_col[c] == -1 && a[r][c] != row[r]) {
      t_col[c] = a[r][c];
      if (!fill_row(t_row, t_col, r + 1, c)) return 0;
    }
    ways[r] = 1;
    return dfs(r + 1, t_row, t_col, ways);
  }
  ways[r] = k;
  std::vector<int> t_col(col);
  int64 ret = 0, candidate = k;
  for (int v = 0; v < n + m; ++v) {
    int not_fill = 0;
    for (auto c: pos[r][v]) {
      not_fill += col[c] == -1;
    }
    if (not_fill == 0) continue;
    --candidate;
    bool valid = true;
    std::vector<int> t_row(row);
    t_row[r] = v;
    for (int c = 0; c < m && valid; ++c) if (col[c] == -1) {
      if (a[r][c] != t_row[r]) {
        t_col[c] = a[r][c];
        if (!fill_row(t_row, t_col, r + 1, c)) valid = false;
      } else t_col[c] = -1;
    }
    ways[r] = 1;
    if (valid) ret += dfs(r + 1, t_row, t_col, ways);
  }
  std::vector<int> t_row(row);
  ways[r] = candidate;
  for (int c = 0; c < m; ++c) if (col[c] == -1) {
    t_col[c] = a[r][c];
    if (!fill_row(t_row, t_col, r + 1, c)) return ret % mod;
  }
  if (candidate) ret += dfs(r + 1, t_row, t_col, ways);
  return ret % mod;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  std::vector<int> xs(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
      xs[i * m + j] = a[i][j];
    }
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  if ((int)xs.size() > n + m || k < (int)xs.size()) {
    puts("0");
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][j] = std::lower_bound(xs.begin(), xs.end(), a[i][j]) - xs.begin();
      pos[i][a[i][j]].push_back(j);
    }
  }
  std::vector<int> row(n, -1), col(m, -1), ways(n, 0);
  int64 ret = dfs(0, row, col, ways);
  printf("%lld\n", ret);
  return 0;
}

#include <cstdio>
#include <vector>
#include <bitset>

const int N = 1e3 + 10, Q = 1e6 + 10;

std::bitset<N> f[N][N], g[N][N];
bool graph[N][N], ans[Q];
int sr[Q], sc[Q], tr[Q], tc[Q];
int n, m, q;

void solve(int l, int r, const std::vector<int> &remain) {
  if (l > r) return;
  int mid = (l + r) >> 1;
  for (int i = mid; i >= l; --i) {
    for (int j = m - 1; j >= 0; --j) {
      f[i][j] = 0;
      if (graph[i][j]) {
        if (i == mid) f[i][j][j] = 1;
        else f[i][j] |= f[i + 1][j];
        if (j != m - 1) f[i][j] |= f[i][j + 1];
      }
    }
  }
  for (int i = mid; i <= r; ++i) {
    for (int j = 0; j < m; ++j) {
      g[i][j] = 0;
      if (graph[i][j]) {
        if (i == mid) g[i][j][j] = 1;
        else g[i][j] |= g[i - 1][j];
        if (j) g[i][j] |= g[i][j - 1];
      }
    }
  }
  std::vector<int> left, right;
  for (auto &&i: remain) {
    if (tr[i] < mid) left.push_back(i);
    else if (sr[i] > mid) right.push_back(i);
    else {
      ans[i] = (f[sr[i]][sc[i]] & g[tr[i]][tc[i]]).any();
    }
  }
  solve(l, mid - 1, left);
  solve(mid + 1, r, right);
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < n; ++i) {
    static char s[N];
    scanf("%s", s);
    for (int j = 0; j < m; ++j) {
      graph[i][j] = s[j] == '.';
    }
  }
  std::vector<int> remain(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d%d%d", sr + i, sc + i, tr + i, tc + i);
    --sr[i], --sc[i], --tr[i], --tc[i];
    remain[i] = i;
  }
  solve(0, n - 1, remain);
  for (int i = 0; i < q; ++i) {
    printf("%s\n", ans[i] ? "YES" : "NO");
  }
  return 0;
}

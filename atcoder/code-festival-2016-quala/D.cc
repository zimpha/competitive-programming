#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

std::vector<std::pair<int, int>> edges[N];
int weight[N], sign[N];
int mark[N];
int left, right;

bool solve(int u, int w, int s) {
  if (mark[u]) return w == weight[u] && sign[u] == s;
  if (s < 0) right = std::min(right, w);
  else left = std::max(left, -w);
  weight[u] = w;
  sign[u] = s;
  mark[u] = 1;
  for (auto &e: edges[u]) {
    if (!solve(e.first, e.second - w, -s)) return false;
  }
  return true;
}

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < q; ++i) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    --x, --y;
    edges[x].emplace_back(y + n, w);
    edges[y + n].emplace_back(x, w);
  }
  for (int i = 0; i < n + m; ++i) if (!mark[i]) {
    left = 0, right = 2e9;
    if (!solve(i, 0, 1)) {
      puts("No");
      return 0;
    }
    if (left > right) {
      puts("No");
      return 0;
    }
  }
  puts("Yes");
  return 0;
}

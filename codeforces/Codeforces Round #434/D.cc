#include <cstdio>
#include <array>
#include <vector>

const int N = 2e5 + 10;

using state = std::array<int, 3>;

std::vector<state> ret;
std::vector<int> edges[N], extra[N];
int mark[N];

int dfs(int u, int p = -1) {
  mark[u] = true;
  std::vector<int> son;
  for (auto &&v: edges[u]) {
    if (v == p) continue;
    if (mark[v]) extra[v].push_back(u);
    else {
      int e = dfs(v, u);
      if (!e) son.push_back(v);
    }
  }
  for (auto &&v: extra[u]) son.push_back(v);
  while (son.size() >= 2) {
    int x = son.back(); son.pop_back();
    int y = son.back(); son.pop_back();
    state s = {x + 1, u + 1, y + 1};
    ret.push_back(s);
  }
  if (son.size() && p != -1) {
    state s = {son[0] + 1, u + 1, p + 1};
    ret.push_back(s);
  }
  return son.size();
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    edges[a - 1].push_back(b - 1);
    edges[b - 1].push_back(a - 1);
  }
  for (int i = 0; i < n; ++i) {
    if (mark[i]) continue;
    dfs(i);
  }
  printf("%d\n", (int)ret.size());
  for (auto &&e: ret) {
    printf("%d %d %d\n", e[0], e[1], e[2]);
  }
  return 0;
}

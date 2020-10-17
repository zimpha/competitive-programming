#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <set>

using int64 = long long;

struct Edge {
  int x, y, nx;
  int64 w;
};

const int N = 2e5 + 10, M = 4e5 + 10;
const int mod = 998244353;

Edge edges[M * 2];
std::vector<int> faces[M];
std::vector<int> belong[M];
std::vector<int> adj[N];
int dsu[N], size[N];
int n, m, nt;

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int main() {
  scanf("%d%d", &n, &m);
  std::set<std::pair<int64, int>> border;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%lld", &edges[i * 2].x, &edges[i * 2].y, &edges[i * 2].w);
    --edges[i * 2].x, --edges[i * 2].y;
    edges[i * 2 + 1].x = edges[i * 2].y;
    edges[i * 2 + 1].y = edges[i * 2].x;
    edges[i * 2 + 1].w = edges[i * 2].w;
    adj[edges[i * 2].x].push_back(i * 2);
    adj[edges[i * 2 + 1].x].push_back(i * 2 + 1);
  }
  for (int i = 0; i < n; ++i) {
    std::sort(adj[i].begin(), adj[i].end(), [&] (int e1, int e2) {
      return (edges[e1].y + n - i) % n < (edges[e2].y + n - i) % n;
    });
    for (size_t j = 0; j < adj[i].size(); ++j) {
      edges[adj[i][j] ^ 1].nx = adj[i][(j + 1) % adj[i].size()];
      if ((edges[adj[i][j]].y + n - i) % n == 1) {
        border.emplace(edges[adj[i][j]].w, adj[i][j] / 2);
      }
    }
  }
  std::vector<bool> visited(m * 2);
  int outer_face = -1;
  nt = 0;
  for (int i = 0; i < m * 2; ++i) if (!visited[i]) {
    bool is_outer_face = true;
    for (int e = i; !visited[e]; e = edges[e].nx) {
      is_outer_face &= (edges[e].x + 1) % n == edges[e].y;
      faces[nt].push_back(e / 2);
      belong[e / 2].push_back(nt);
      visited[e] = true;
    }
    if (is_outer_face) outer_face = nt;
    nt++;
  }
  std::vector<bool> mark(nt);
  std::vector<int> order;
  mark[outer_face] = true;
  while (!border.empty()) {
    int64 w = border.begin()->first;
    int e = border.begin()->second;
    border.erase(border.begin());
    bool found = false;
    for (auto &f_id: belong[e]) if (!mark[f_id]) {
      mark[f_id] = true;
      found = true;
      for (auto i: faces[f_id]) if (i != e) {
        border.erase({edges[i * 2].w, i});
        edges[i * 2].w += w;
        border.emplace(edges[i * 2].w, i);
      }
    }
    if (!found) order.push_back(e * 2);
  }

  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    dsu[i] = i; size[i] = 1;
  }
  std::reverse(order.begin(), order.end());
  for (auto &e: order) {
    int x = get(edges[e].x);
    int y = get(edges[e].y);
    assert(x != y);
    ret += edges[e].w % mod * size[x] % mod * size[y] % mod;
    dsu[x] = y; size[y] += size[x];
  }
  printf("%lld\n", ret % mod);
  return 0;
}

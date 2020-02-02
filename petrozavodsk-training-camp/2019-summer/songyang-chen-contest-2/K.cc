#include <cstdio>
#include <vector>
#include <queue>

const int N = 2e5 + 10;
using int64 = long long;

std::vector<int> edges[N];
int dsu[N], parent[N];

struct Node {
  int64 a, b;
  int id;
  void merge(int64 u, int64 v) {
    int64 x = std::max(a, u + a - b);
    int64 y = b - a + v - u + x;
    a = x, b = y;
  }
  bool operator < (const Node& rhs) const {
    int s1 = a > b ? -1 : a < b;
    int s2 = rhs.a > rhs.b ? -1 : rhs.a < rhs.b;
    if (s1 != s2) return s1 < s2;
    return s1 < 0 ? b < rhs.b : a > rhs.a;
  }
};

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void dfs(int u, int p = -1) {
  for (auto &v: edges[u]) if (v != p) {
    parent[v] = u;
    dfs(v, u);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m = 0;
    scanf("%d", &n);
    std::priority_queue<Node> pq;
    std::vector<Node> monster;
    monster.emplace_back();
    for (int i = 1; i < n; ++i) {
      int64 a, b;
      scanf("%lld%lld", &a, &b);
      monster.push_back((Node){a, b, ++m});
      pq.push(monster.back());
    }
    for (int i = 0; i < n; ++i) {
      dsu[i] = i;
      edges[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges[u - 1].push_back(v - 1);
      edges[v - 1].push_back(u - 1);
    }
    dfs(0);
    std::vector<Node> hit;
    std::vector<bool> mark(n * 2);
    mark[0] = 1;
    while (!pq.empty()) {
      auto u = pq.top(); pq.pop();
      if (mark[u.id]) continue;
      int v = get(parent[u.id]);
      if (mark[v]) hit.push_back(u), mark[u.id] = 1;
      else {
        m++;
        monster.push_back(monster[v]);
        mark[u.id] = mark[v] = 1;
        dsu[u.id] = dsu[v] = dsu[m] = m;
        parent[m] = parent[v];
        monster.back().id = m;
        monster.back().merge(u.a, u.b);
        pq.push(monster.back());
      }
    }
    int64 ret = 0;
    while (!hit.empty()) {
      ret = std::max(hit.back().a, ret - hit.back().b + hit.back().a);
      hit.pop_back();
    }
    printf("%lld\n", ret);
  }
  return 0;
}

#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>

const int N = 2e5 + 10;

struct Node {
  Node* ch[2];
  std::set<int> s;
} *root;

std::vector<std::pair<int, int>> edges[N];
int val[N], st[N], ed[N], sz;

void dfs(int u) {
  st[u] = sz++;
  for (auto &e: edges[u]) {
    int v = e.first, w = e.second;
    val[v] = val[u] ^ w;
    dfs(v);
  }
  ed[u] = sz;
}

void ins(int u) {
  auto p = root;
  for (int i = 30; i >= 0; --i) {
    int o = val[u] >> i & 1;
    if (!p->ch[o]) p->ch[o] = new Node();
    p = p->ch[o];
    p->s.insert(st[u]);
  }
}

bool check(const std::set<int> &s, int l, int r) {
  auto it = s.lower_bound(l);
  return it != s.end() && *it < r;
}

int query(int u, int v) {
  int ret = 0;
  int l = st[v], r = ed[v];
  auto p = root;
  for (int i = 30; i >= 0; --i) {
    int o = (val[u] >> i & 1) ^ 1;
    if (p->ch[o] && check(p->ch[o]->s, l, r)) p = p->ch[o], ret ^= 1 << i;
    else p = p->ch[o ^ 1];
  }
  return ret;
}

int main() {
  int q;
  scanf("%d", &q);
  std::vector<std::pair<int, int>> queries(q);
  int n = 1;
  for (int i = 0; i < q; ++i) {
    char op[10];
    int x, y;
    scanf("%s%d%d", op, &x, &y);
    if (op[0] == 'A') {
      edges[x - 1].emplace_back(n++, y);
      queries[i] = {-1, n - 1};
    } else {
      queries[i] = {x - 1, y - 1};
    }
  }
  dfs(0);

  root = new Node();
  ins(0);
  for (int i = 0; i < q; ++i) {
    if (queries[i].first == -1) ins(queries[i].second);
    else printf("%d\n", query(queries[i].first, queries[i].second));
  }
  return 0;
}

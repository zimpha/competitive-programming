#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

const int N = 2e6 + 10;
const int mod = 1e9 + 7;

using int64 = long long;

char s[N];

struct Node {
  int idx;
  std::vector<int> child;
} nodes[N];

int mark[N];
int size[N], col[N];
std::vector<int> edges[N];
int p, nt, ng;

int build_tree(int size) {
  int root = nt++;
  nodes[root].idx = -1;
  if (s[p] == '4') {
    ++p;
    for (int i = 0; i < 4; ++i) {
      nodes[root].child.push_back(build_tree(size - 1));
    }
  } else {
    ::col[ng] = s[p++] - '0';
    ::size[ng] = size;
    nodes[root].idx = ng++;
  }
  return root;
}

void build_graph_hor(int u, int v) {
  if (nodes[u].idx != -1 && nodes[v].idx != -1) {
    if (col[nodes[u].idx] && col[nodes[v].idx]) {
      edges[nodes[u].idx].push_back(nodes[v].idx);
      edges[nodes[v].idx].push_back(nodes[u].idx);
    }
    return;
  }
  if (nodes[u].idx == -1 && nodes[v].idx == -1) {
    build_graph_hor(nodes[u].child[1], nodes[v].child[0]);
    build_graph_hor(nodes[u].child[3], nodes[v].child[2]);
  } else if (nodes[u].idx != -1) {
    build_graph_hor(u, nodes[v].child[0]);
    build_graph_hor(u, nodes[v].child[2]);
  } else {
    build_graph_hor(nodes[u].child[1], v);
    build_graph_hor(nodes[u].child[3], v);
  }
}

void build_graph_ver(int u, int v) {
  if (nodes[u].idx != -1 && nodes[v].idx != -1) {
    if (col[nodes[u].idx] && col[nodes[v].idx]) {
      edges[nodes[u].idx].push_back(nodes[v].idx);
      edges[nodes[v].idx].push_back(nodes[u].idx);
    }
    return;
  }
  if (nodes[u].idx == -1 && nodes[v].idx == -1) {
    build_graph_ver(nodes[u].child[2], nodes[v].child[0]);
    build_graph_ver(nodes[u].child[3], nodes[v].child[1]);
  } else if (nodes[u].idx != -1) {
    build_graph_ver(u, nodes[v].child[0]);
    build_graph_ver(u, nodes[v].child[1]);
  } else {
    build_graph_ver(nodes[u].child[2], v);
    build_graph_ver(nodes[u].child[3], v);
  }
}

void build_graph(int u) {
  if (nodes[u].idx != -1) return;
  build_graph_hor(nodes[u].child[0], nodes[u].child[1]);
  build_graph_hor(nodes[u].child[2], nodes[u].child[3]);

  build_graph_ver(nodes[u].child[0], nodes[u].child[2]);
  build_graph_ver(nodes[u].child[1], nodes[u].child[3]);
  for (auto &v: nodes[u].child) build_graph(v);
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int m;
  scanf("%d%s", &m, s);
  p = nt = ng = 0;
  int root = build_tree(m);
  build_graph(root);
  int ret = 0;
  std::map<int, int> best;

  auto cmp = [&](const std::map<int, int> &a, const std::map<int, int> &b) {
    auto ia = a.rbegin(), ib = b.rbegin();
    while (ia != a.rend() && ib != b.rend()) {
      if (ia->first != ib->first) return ia->first > ib->first;
      else if (ia->second != ib->second) return ia->second > ib->second;
      ++ia, ++ib;
    }
    return ia != a.rend();
  };

  for (int i = 0; i < ng; ++i) if (col[i] && !mark[i]) {
    std::vector<int> queue = {i};
    mark[i] = 1;
    for (size_t h = 0; h < queue.size(); ++h) {
      int u = queue[h];
      for (auto &v: edges[u]) if (!mark[v]) {
        queue.push_back(v);
        mark[v] = 1;
      }
    }
    std::map<int, int> cnt;
    for (auto &u: queue) cnt[size[u]]++;
    for (auto it = cnt.begin(); it != cnt.end(); ) {
      if (it->second >= 4) {
        cnt[it->first + 1] += it->second / 4;
      }
      it->second %= 4;
      if (it->second == 0) it = cnt.erase(it);
      else ++it;
    }
    if (cmp(cnt, best)) best = cnt;
    ++ret;
  }
  printf("%d\n", ret);
  int64 cnt = 0;
  for (auto &e: best) cnt += pow_mod(4, e.first) * e.second % mod;
  printf("%lld\n", cnt % mod);
  return 0;
}

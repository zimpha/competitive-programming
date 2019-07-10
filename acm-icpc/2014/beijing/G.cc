#include <cstdio>
#include <cassert>
#include <queue>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <iostream>

using int64 = long long;

const int64 bound = 1e9;

struct Node {
  std::vector<int> children;
  std::vector<std::pair<int, int>> edges;
  std::vector<int64> ways;
  int64 lsum, lsum_prefix;
  int parent[20];
  int depth;
  int sep;
  bool special;
};

int solve(int s, int k, std::vector<Node>& nodes) {
  if (nodes[s].ways.empty() || nodes[s].ways.back() < k) {
    return -1;
  }
  auto up = [&] (int u, int d) {
    for (int i = 0; d; ++i, d >>= 1) {
      if (d & 1) u = nodes[u].parent[i];
    }
    return u;
  };

  int ret = 0;
  while (nodes[s].sep != -1) {
    assert(nodes[s].ways.back() >= k);
    // no jump
    auto it = std::lower_bound(
        nodes[s].ways.begin(),
        nodes[s].ways.end(),
        k) - nodes[s].ways.begin();
    if (nodes[s].lsum >= k) {
      if (it != 0) k -= nodes[s].ways[it - 1];
      ++ret;
      s = nodes[s].edges[it].second;
    } else if (k > nodes[s].ways[nodes[s].sep]) {
      if (it != 0) k -= nodes[s].ways[it - 1];
      ++ret;
      s = nodes[s].edges[it].second;
    } else {
      int l = 1, r = nodes[s].depth;
      if (nodes[s].lsum_prefix < k) { // jump right
        while (l < r) {
          int m = (l + r - 1) >> 1;
          int p = up(s, m);
          int64 ways_p = nodes[p].sep == -1 ? 0 : nodes[p].ways[nodes[p].sep];
          if (k > nodes[s].lsum_prefix - nodes[p].lsum_prefix + ways_p) r = m;
          else l = m + 1;
        }
        ret += l;
        int p = up(s, l);
        k -= nodes[s].lsum_prefix - nodes[p].lsum_prefix;
        auto it = std::lower_bound(
            nodes[p].ways.begin(),
            nodes[p].ways.end(),
            k) - nodes[p].ways.begin();
        k -= it ? nodes[p].ways[it - 1] : 0;
        ++ret;
        s = nodes[p].edges[it].second;
      } else { // jump left
        while (l < r) {
          int m = (l + r - 1) >> 1;
          int p = up(s, m);
          if (k <= nodes[s].lsum_prefix - nodes[p].lsum_prefix + nodes[p].lsum) r = m;
          else l = m + 1;
        }
        ret += l;
        int p = up(s, l);
        k -= nodes[s].lsum_prefix - nodes[p].lsum_prefix;
        if (k == 1 && nodes[p].special) break;
        auto it = std::lower_bound(
            nodes[p].ways.begin(),
            nodes[p].ways.end(),
            k) - nodes[p].ways.begin();
        k -= it ? nodes[p].ways[it - 1] : 0;
        ++ret;
        s = nodes[p].edges[it].second;
      }
    }
  }
  return ret - 1;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    std::vector<int> s(n);
    int nn = n;
    for (int i = 1; i < n; ++i) {
      scanf("%d", &s[i]);
      nn += s[i];
    }
    std::vector<std::vector<int>> pred(nn);
    std::vector<int> deg(nn);
    std::vector<Node> nodes(nn);
    std::vector<int64> ways(nn);
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      --u, --v ;
      nodes[u].edges.emplace_back(w, v);
      pred[v].push_back(u);
      ++deg[u];
    }
    nn = n;
    for (int i = 1; i < n; ++i) if (s[i] == 1) {
      nodes[i].edges.emplace_back(-1, nn);
      nodes[nn].special = ways[nn] = 1;
      pred[nn++].push_back(i);
      ++deg[i];
    }
    n = nn;
    std::vector<int> queue;
    for (int i = 0; i < n; ++i) {
      if (deg[i] == 0) queue.push_back(i);
    }
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      ways[u] = std::min(ways[u], bound);
      for (auto &v : pred[u]) {
        ways[v] += ways[u];
        if (--deg[v] == 0) queue.push_back(v);
      }
    }
    for (int i = 0; i < n; ++i) {
      std::sort(nodes[i].edges.begin(), nodes[i].edges.end());
      memset(nodes[i].parent, -1, sizeof(nodes[i].parent));
      for (auto &e : nodes[i].edges) {
        nodes[i].ways.push_back(ways[e.second]);
      }
      if (nodes[i].edges.size()) {
        nodes[i].sep = std::max_element(
          nodes[i].ways.begin(),
          nodes[i].ways.end()) - nodes[i].ways.begin();
      } else {
        nodes[i].sep = -1;
      }
      for (size_t j = 1; j < nodes[i].edges.size(); ++j) {
        nodes[i].ways[j] += nodes[i].ways[j - 1];
      }
      if (nodes[i].sep != -1) {
        nodes[i].parent[0] = nodes[i].edges[nodes[i].sep].second;
        nodes[nodes[i].parent[0]].children.push_back(i);
      }
      if (nodes[i].sep > 0) {
        nodes[i].lsum = nodes[i].ways[nodes[i].sep - 1];
      }
      if (nodes[i].special) nodes[i].lsum = 1;
    }
    for (int b = 1; (1 << b) <= n; ++b) {
      for (int i = 0; i < n; ++i) if (nodes[i].parent[b - 1] != -1) {
        nodes[i].parent[b] = nodes[nodes[i].parent[b - 1]].parent[b - 1];
      }
    }
    std::function<void(int, int)> dfs = [&] (int u, int p = -1) {
      nodes[u].depth = 1;
      nodes[u].lsum_prefix = nodes[u].lsum;
      if (p != -1) {
        nodes[u].depth += nodes[p].depth;
        nodes[u].lsum_prefix += nodes[p].lsum_prefix;
      }
      for (auto &v : nodes[u].children) {
        dfs(v, u);
      }
    };
    for (int i = 0; i < n; ++i) if (nodes[i].parent[0] == -1) {
      dfs(i, -1);
    }
    printf("Case #%d:\n", cas);
    for (int k; q--; ) {
      scanf("%d", &k);
      printf("%d\n", solve(0, k, nodes));
    }
  }
  return 0;
}

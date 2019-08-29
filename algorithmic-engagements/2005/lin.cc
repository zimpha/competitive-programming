#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> deg(n);
  std::vector<std::pair<int, int>> el;
  el.reserve(m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    ++deg[--a], ++deg[--b];
    el.emplace_back(a, b);
  }
  std::vector<std::vector<int>> edges(n);
  std::vector<int> dsu(n);
  for (int i = 0; i < n; ++i) dsu[i] = i;
  std::function<int(int)> root = [&](int x) {
    if (dsu[x] != x) dsu[x] = root(dsu[x]);
    return dsu[x];
  };

  for (int i = 0; i < m; ++i) {
    int a = root(el[i].first);
    int b = root(el[i].second);
    if (a != b) {
      edges[el[i].first].push_back(i);
      edges[el[i].second].push_back(i);
      dsu[a] = b;
    }
  }

  std::vector<int> next(n, -1);
  std::vector<int> mark(m);
  std::vector<std::vector<int>> paths;
  std::function<bool(int, int)> dfs1 = [&](int u, int p) {
    std::vector<int> vs;
    for (auto &e: edges[u]) {
      int v = el[e].first + el[e].second - u;
      if (v == p) continue;
      if (dfs1(v, u)) vs.push_back(e);
    }
    while (vs.size() > 1) {
      int a = vs.back(); vs.pop_back();
      int b = vs.back(); vs.pop_back();
      mark[a] = mark[b] = 1;
      int x = el[a].first + el[a].second - u;
      int y = el[b].first + el[b].second - u;
      paths.emplace_back();
      auto &path = paths.back();
      path.push_back(u);
      while (next[x] != -1) {
        mark[next[x]] = 1;
        path.push_back(x);
        x = el[next[x]].first + el[next[x]].second - x;
      }
      path.push_back(x);
      std::reverse(path.begin(), path.end());
      while (next[y] != -1) {
        mark[next[y]] = 1;
        path.push_back(y);
        y = el[next[y]].first + el[next[y]].second - y;
      }
      path.push_back(y);
    }
    if (vs.empty()) return deg[u] % 2 == 1;
    else {
      next[u] = vs[0];
      if (deg[u] % 2 == 1) {
        paths.emplace_back();
        auto &path = paths.back();
        while (next[u] != -1) {
          mark[next[u]] = 1;
          path.push_back(u);
          u = el[next[u]].first + el[next[u]].second - u;
        }
        path.push_back(u);
        return false;
      } else {
        return true;
      }
    }
  };
  dfs1(0, -1);

  for (int i = 0; i < n; ++i) edges[i].clear();
  for (int i = 0; i < n; ++i) deg[i] = 0;
  for (int i = 0; i < m; ++i) if (!mark[i]) {
    edges[el[i].first].push_back(i);
    edges[el[i].second].push_back(i);
    ++deg[el[i].first];
    ++deg[el[i].second];
  }
  for (int i = 0; i < n; ++i) {
    assert(deg[i] % 2 == 0);
  }
  std::vector<int> head(n, 0);
  std::vector<int> cycle;
  std::function<void(int)> dfs2 = [&](int x) {
    for (int &i = head[x]; i < (int)edges[x].size(); ++i) {
      int e = edges[x][i];
      if (mark[e]) continue;
      mark[e] = 1;
      dfs2(el[e].first + el[e].second - x);
    }
    cycle.push_back(x);
  };

  if (paths.empty()) {
    dfs2(0);
    puts("1");
    printf("%d", (int)cycle.size());
    for (auto &x: cycle) printf(" %d", x + 1);
    puts("");
  } else {
    printf("%d\n", (int)paths.size());
    for (auto &path: paths) {
      std::vector<int> result;
      for (auto &x: path) {
        if (deg[x] && head[x] == 0) {
          cycle.clear();
          dfs2(x);
          for (auto &y: cycle) result.push_back(y + 1);
        } else {
          result.push_back(x + 1);
        }
      }
      printf("%d", (int)result.size());
      for (auto &x: result) printf(" %d", x);
      puts("");
    }
  }
  return 0;
}

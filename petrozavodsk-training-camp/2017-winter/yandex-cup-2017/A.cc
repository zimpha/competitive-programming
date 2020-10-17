#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int N = 100000 + 10, M = 100000 + 10;

struct tri_t {
  int u, v, w;
  tri_t() {}
  tri_t(int u, int v, int w): u(u), v(v), w(w) {}
};

int u[M], v[M], w[M];
int deg[N];
std::vector<int> graph[N];
std::vector<tri_t> triangle[N];
std::vector<tri_t> best[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", u + i, v + i, w + i);
    ++deg[--u[i]];
    ++deg[--v[i]];
  }
  for (int i = 0; i < m; ++i) {
    if (deg[u[i]] < deg[v[i]]) {
      graph[u[i]].push_back(i);
    } else {
      graph[v[i]].push_back(i);
    }
  }
  auto to = [&] (int e, int a) {
    return u[e] + v[e] - a;
  };
  std::vector<int> mark(n, -1);
  for (int a = 0; a < N; ++a) {
    for (auto &&e: graph[a]) {
      mark[to(e, a)] = e;
    }
    for (auto &&e: graph[a]) {
      int b = to(e, a);
      for (auto &&t: graph[b]) {
        int c = to(t, b);
        if (mark[c] != -1) {
          int weight = w[e] + w[t] + w[mark[c]];
          triangle[a].emplace_back(b, c, weight);
          triangle[b].emplace_back(a, c, weight);
          triangle[c].emplace_back(a, b, weight);
        }
      }
    }
    for (auto &&e: graph[a]) {
      mark[to(e, a)] = -1;
    }
  }
  auto add_tri = [](std::vector<tri_t> &tri, const tri_t &e, int k) {
    tri.push_back(e);
    std::sort(tri.begin(), tri.end(), [] (const tri_t &a, const tri_t &b) {
        return a.w > b.w;
        });
    if (tri.size() == k) {
      tri.pop_back();
    }
  };
  int current = 0;
  auto solve = [&] (const std::vector<tri_t> &tri) {
    ++current;
    std::vector<tri_t> global;
    std::vector<int> candidate;
    for (auto &&e: tri) {
      if (mark[e.u] != current) {
        mark[e.u] = current;
        best[e.u].clear();
        candidate.push_back(e.u);
      }
      if (mark[e.v] != current) {
        mark[e.v] = current;
        best[e.v].clear();
        candidate.push_back(e.v);
      }
      add_tri(best[e.u], e, 4);
      add_tri(best[e.v], e, 4);
    }
    for (auto &&u: candidate) {
      for (auto &&e: best[u]) {
        add_tri(global, e, 12);
      }
    }
    int ret = -1;
    for (auto &&u: candidate) {
      for (auto &&e1: best[u]) {
        for (auto &&e2: global) {
          if (e1.u != e2.u && e1.u != e2.v && e1.v != e2.u && e1.v != e2.v) {
            if (ret == -1 || ret < e1.w + e2.w) {
              ret = e1.w + e2.w;
            }
          }
        }
      }
    }
    return ret;
  };
  int ret = -1;
  for (int a = 0; a < N; ++a) {
    int now = solve(triangle[a]);
    if (ret == -1 || now > ret) {
      ret = now;
    }
  }
  printf("%d\n", ret);
  return 0;
}

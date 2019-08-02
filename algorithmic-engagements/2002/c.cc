#include <cstdio>
#include <vector>

int main() {
  int a, n, b, k, m;
  scanf("%d%d%d%d%d", &a, &n, &b, &k, &m);
  std::vector<int> forbid(a + n + b);
  std::vector<std::vector<int>> edges(a + n + b);
  std::vector<int> p(k);
  for (int i = a + n; i < a + n + b; ++i) {
    forbid[i] = 1;
  }
  for (int i = 0; i < k; ++i) {
    scanf("%d", &p[i]);
    p[i]--;
    forbid[p[i]] = 1;
  }
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x, --y;
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  std::vector<int> s, t;
  int ret = -1;
  for (int i = 0; i < a; ++i) s.push_back(i);
  for (int i = 0; i <= k; ++i) {
    if (i < k) {
      t = {p[i]};
      forbid[p[i]] = 0;
    } else {
      t.clear();
      for (int j = a + n; j < a + n + b; ++j) {
        forbid[j] = 0;
        t.push_back(j);
      }
    }
    std::vector<int> queue;
    std::vector<int> dis(a + n + b, -1);
    for (auto &x: s) {
      queue.push_back(x);
      dis[x] = 0;
    }
    for (size_t j = 0; j < queue.size(); ++j) {
      int u = queue[j];
      for (auto &&v: edges[u]) {
        if (dis[v] == -1 && !forbid[v]) {
          dis[v] = dis[u] + 1;
          queue.push_back(v);
        }
      }
    }
    int mx = -1;
    for (auto &x: t) if (dis[x] != -1) {
      if (mx == -1 || mx > dis[x]) mx = dis[x];
    }
    if (mx == -1) {
      ret = -1;
      break;
    }
    ret += mx;
    if (i == 0) {
      for (auto &x: s) forbid[x] = 1;
    }
    s.swap(t);
  }
  printf("%d\n", ret);
  return 0;
}

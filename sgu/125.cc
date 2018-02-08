#include <cstdio>
#include <vector>
#include <cstring>
#include <vector>

int dsu[9], a[9], b[9], cnt[9];
int deg[9];
std::vector<int> g[9];

int get(int x) {
  if (dsu[x] != x) dsu[x] = get(dsu[x]);
  return dsu[x];
}

bool valid(int n) {
  for (int i = 0; i < n; ++i) deg[i] = a[i] = 0;
  for (int i = 0; i < n; ++i) {
    for (auto &&j: g[i]) deg[j]++;
  }
  std::vector<int> queue;
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) {
      queue.push_back(i);
      a[i] = 0;
    }
  }
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &&v: g[u]) {
      a[v] = std::max(a[v], a[u] + 1);
      if (--deg[v] == 0) queue.push_back(v);
    }
  }
  if (queue.size() != n) return false;
  for (int i = 0; i < n; ++i) {
    a[i] = a[get(i)];
  }
  return true;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n * n; ++i) {
    scanf("%d", &b[i]);
  }
  auto id = [&n](int x, int y) {return x * n + y;};
  std::vector<int> edges;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i + 1 < n) edges.push_back(id(i, j) * n * n + id(i + 1, j));
      if (j + 1 < n) edges.push_back(id(i, j) * n * n + id(i, j + 1));
    }
  }
  int m = edges.size();
  int pw[m + 1] = {1};
  for (int i = 1; i <= m; ++i) pw[i] = pw[i - 1] * 3;
  for (int mask = 0; mask < pw[m]; ++mask) {
    for (int i = 0; i < n * n; ++i) {
      dsu[i] = i;
      cnt[i] = 0;
      g[i].clear();
    }
    for (int i = 0; i < m; ++i) {
      int o = mask / pw[i] % 3;
      int x = edges[i] / (n * n), y = edges[i] % (n * n);
      // 0, 1, 2: < = >
      if (o == 0) cnt[x]++;
      if (o == 2) cnt[y]++;
      if (o == 1) {
        x = get(x);
        y = get(y);
        dsu[x] = y;
      }
    }
    bool flag = true;
    for (int i = 0; i < n * n; ++i) {
      if (b[i] != cnt[i]) flag = false;
    }
    if (!flag) continue;
    for (int i = 0; i < m; ++i) {
      int o = mask / pw[i] % 3;
      if (o == 1) continue;
      int x = get(edges[i] / (n * n)), y = get(edges[i] % (n * n));
      if (o == 0) g[x].push_back(y);
      if (o == 2) g[y].push_back(x);
    }
    if (valid(n * n)) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (j) putchar(' ');
          printf("%d", a[i * n + j]);
        }
        puts("");
      }
      return 0;
    }
  }
  puts("NO SOLUTION");
  return 0;
}

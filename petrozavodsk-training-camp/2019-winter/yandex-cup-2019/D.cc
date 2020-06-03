#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <vector>

using int64 = long long;

const int M = 5000 + 10;
const int N = 60;

struct Base {
  constexpr static int LOG = 60;
  std::vector<int64> b;

  Base() {
    b.assign(LOG, 0);
  }

  void clear() {
    for (int i = 0; i < LOG; ++i) b[i] = 0;
  }

  void append(int64 x) {
    for (int i = 0; i < LOG; ++i) if (x >> i & 1) {
      if (b[i]) x ^= b[i];
      else { b[i] = x; return; }
    }
  }

  bool check(int64 x) {
    for (int i = 0; i < LOG; ++i) if (x >> i & 1) {
      if (b[i]) x ^= b[i];
      else return true;
    }
    return false;
  }
} base;

int na, nb;
int64 a[N];

namespace matroid {
  int64 val[M], col[M];
  bool choose[M], has_col[N];
  bool ok[2][M];
  int m;

  void add(int64 v, int c) {
    val[m] = v, col[m] = c;
    choose[m++] = false;
  }

  bool aug() {
    std::vector<int> cidx;
    for (int i = 0; i < m; ++i) {
      if (choose[i]) cidx.push_back(i);
      ok[0][i] = ok[1][i] = 0;
    }
    // I + y is independent
    base.clear();
    for (int i = 0; i < na; ++i) base.append(a[i]);
    for (auto &x: cidx) base.append(val[x]);
    for (int y = 0; y < m; ++y) if (!choose[y]) {
      if (base.check(val[y])) ok[0][y] = 1;
    }
    // I + y has unique color
    for (int y = 0; y < m; ++y) if (!choose[y]) {
      if (!has_col[col[y]]) ok[1][y] = 1;
    }
    for (int i = 0; i < m; ++i) if (ok[0][i] && ok[1][i]) {
      choose[i] = 1;
      has_col[col[i]] = true;
      return true;
    }
    std::vector<int> dist(m, -1), from(m, -1);
    std::vector<int> queue;
    for (int x = 0; x < m; ++x) if (ok[0][x]) {
      queue.push_back(x);
      dist[x] = 0;
    }
    int best = -1;
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      if (ok[1][u]) { best = u; break; }
      std::vector<int> go;
      if (choose[u]) {
        // I - u + v is independent
        base.clear();
        for (int i = 0; i < na; ++i) base.append(a[i]);
        for (auto &i: cidx) if (i != u) {
          base.append(val[i]);
        }
        for (int v = 0; v < m; ++v) if (!choose[v] && dist[v] == -1) {
          if (base.check(val[v])) go.push_back(v);
        }
      } else {
        // I + u - v has unique color
        for (auto &v: cidx) if (dist[v] == -1) {
          if (has_col[col[u]] == (col[u] == col[v])) go.push_back(v);
        }
      }
      for (auto &v: go) if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        from[v] = u;
        queue.push_back(v);
      }
    }
    for (int u = best; u != -1; u = from[u]) {
      has_col[col[u]] ^= 1;
      choose[u] ^= 1;
    }
    return best != -1;
  }
}

int main() {
  scanf("%d", &na);
  for (int i = 0; i < na; ++i) {
    scanf("%lld", &a[i]);
  }
  scanf("%d", &nb);
  for (int i = 0, k; i < nb; ++i) {
    scanf("%d", &k);
    for (int j = 0; j < k; ++j) {
      int64 x;
      scanf("%lld", &x);
      matroid::add(x, i);
    }
  }
  base.clear();
  for (int i = 0; i < na; ++i) {
    if (!base.check(a[i])) {
      puts("-1");
      return 0;
    }
    base.append(a[i]);
  }
  int cnt = 0;
  while (matroid::aug()) {
    ++cnt;
  }
  if (cnt != nb) puts("-1");
  else {
    for (int i = 0; i < matroid::m; ++i) {
      if (matroid::choose[i]) {
        printf("%lld\n", matroid::val[i]);
      }
    }
  }
  return 0;
}

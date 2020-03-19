#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1000;

struct Set {
  int parent[N], deg[N];
  void init(int n) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
      deg[i] = 0;
    }
  }
  void merge(int a, int b) {
    deg[a]++, deg[b]++;
    a = root(a), b = root(b);
    if (a != b) parent[a] = b;
  }
  int root(int x) {
    if (x != parent[x]) parent[x] = root(parent[x]);
    return parent[x];
  }
} dsu;

int graph[N][N];

struct Matroid {
  int from[N], to[N], choose[N], m;
  int *bound;

  void init() { m = 0; }

  void add_edge(int u, int v) {
    choose[m] = 0;
    from[m] = u;
    to[m++] = v;
  }

  bool check_degree(int a, int b) {
    return dsu.deg[a] < bound[a] && dsu.deg[b] < bound[b];
  }

  bool aug(int n) {
    std::vector<int> st, ed;
    dsu.init(n);
    for (int x = 0; x < m; ++x) if (choose[x]) {
      dsu.merge(from[x], to[x]);
    }
    for (int i = 0; i < m; ++i) {
      if (check_degree(from[i], to[i])) ed.push_back(i);
      if (dsu.root(from[i]) != dsu.root(to[i])) st.push_back(i);
    }
    if (st.empty() || ed.empty()) return false;
    for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) graph[i][j] = 0;
    for (int x = 0; x < m; ++x) if (choose[x]) {
      dsu.init(n);
      for (int i = 0; i < m; ++i) if (choose[i] && i != x) {
        dsu.merge(from[i], to[i]);
      }
      for (int y = 0; y < m; ++y) if (!choose[y]) {
        graph[y][x] = check_degree(from[y], to[y]);
        graph[x][y] = dsu.root(from[y]) != dsu.root(to[y]);
      }
    }
    std::vector<int> queue = {st};
    std::vector<int> dis(m, -1), parent(m, -1);
    for (auto &x: st) dis[x] = 0;
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      for (int v = 0; v < m; ++v) if (graph[u][v] && dis[v] == -1) {
        dis[v] = dis[u] + 1;
        parent[v] = u;
        queue.push_back(v);
      }
    }
    int best = -1;
    for (auto &x: ed) if (dis[x] != -1) {
      if (best == -1 || dis[x] < dis[best]) best = x;
    }
    for (int x = best; x != -1; x = parent[x]) {
      choose[x] ^= 1;
    }
    return best != -1;
  }
  int solve(int n, std::vector<int> &bound) {
    this->bound = bound.data();
    while (aug(n));
    int cnt = 0;
    for (int i = 0; i < m; ++i) cnt += choose[i];
    return cnt;
  }
} matroid;

char s[N][N], ret[N][N];
int idx[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%s", s[i]);
    int sz = 0;
    std::vector<std::pair<int, int>> cells;
    std::vector<int> bound;
    matroid.init();
    int cnt_special = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (s[i][j] == 'X') continue;
        cells.emplace_back(i, j);
        idx[i][j] = sz++;
        if (i && s[i - 1][j] == 'O' && (i - 1 + j)) matroid.add_edge(idx[i - 1][j], idx[i][j]);
        if (j && s[i][j - 1] == 'O' && (i - 1 + j)) matroid.add_edge(idx[i][j - 1], idx[i][j]);
        if (i % 2 == j % 2 && i + j) bound.push_back(2), ++cnt_special;
        else bound.push_back(4);
      }
    }
    int cnt = matroid.solve(sz, bound);
    if (cnt < cnt_special * 2) puts("NO");
    else {
      if (s[0][1] == 'O') matroid.add_edge(idx[0][0], idx[0][1]);
      if (s[1][0] == 'O') matroid.add_edge(idx[0][0], idx[1][0]);
      dsu.init(sz);
      for (int i = 0; i < matroid.m; ++i) if (matroid.choose[i]) {
        dsu.merge(matroid.from[i], matroid.to[i]);
      }
      for (int i = 0; i < matroid.m; ++i) if (!matroid.choose[i]) {
        int u = matroid.from[i], v = matroid.to[i];
        if (dsu.root(u) != dsu.root(v)) {
          dsu.merge(u, v);
          matroid.choose[i] = 1;
        }
      }
      for (int i = 0; i < 2 * n - 1; ++i) {
        for (int j = 0; j < 2 * m; ++j) ret[i][j] = ' ';
        ret[i][2 * m - 1] = 0;
      }
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          ret[2 * i][2 * j] = s[i][j];
        }
      }
      for (size_t i = 0; i < matroid.m; ++i) {
        int u = matroid.from[i], v = matroid.to[i];
        int x1 = cells[u].first, y1 = cells[u].second;
        int x2 = cells[v].first, y2 = cells[v].second;
        if (matroid.choose[i]) {
          if (x1 == x2) ret[2 * x1][2 * y1 + 1] = 'O';
          else ret[2 * x1 + 1][2 * y1] = 'O';
        } else {
          if (x1 == x2) ret[2 * x1][2 * y1 + 1] = ' ';
          else ret[2 * x1 + 1][2 * y1] = ' ';
        }
      }
      puts("YES");
      for (int i = 0; i < 2 * n - 1; ++i) puts(ret[i]);
    }
  }
  return 0;
}

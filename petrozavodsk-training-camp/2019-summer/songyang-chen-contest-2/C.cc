#include <cstdio>
#include <vector>
#include <queue>

const int N = 100, inf = 1e9;

using pii = std::pair<int, int>;

pii operator + (const pii &a, const pii &b) {
  return {a.first + b.first, a.second + b.second};
}

namespace dsu{
int dsu[N], cc;
void init(int n) {
  for (int i = 0; i < n; ++i) dsu[i] = i;
  cc = n;
}
int root(int x) {
  if (x != dsu[x]) dsu[x] = root(dsu[x]);
  return dsu[x];
}
void merge(int a, int b, int id) {
  a = root(a), b = root(b);
  if (a != b) dsu[a] = b, --cc;
}
}

namespace matroid {
int a[N], b[N], w[N], id[N];
int choose[N], graph[N][N], m;
int cnt[N];

void init() { m = 0; }
void add_edge(int _a, int _b, int _w, int _id) {
  a[m] = _a, b[m] = _b, w[m] = _w; id[m] = _id;
  choose[m++] = 0;
}
bool aug(int n, std::vector<int> &bound) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) graph[i][j] = 0;
  }
  std::vector<int> st, ed;
  for (int y = 0; y < m; ++y) if (!choose[y]) {
    for (size_t i = 0; i < bound.size(); ++i) cnt[i] = 0;
    dsu::init(n);
    for (int i = 0; i < m; ++i) if (!choose[i] && i != y) {
      dsu::merge(a[i], b[i], id[i]);
      cnt[id[i]]++;
    }
    int invalid = 0;
    for (size_t i = 0; i < bound.size(); ++i) invalid += cnt[i] < bound[i];
    if (dsu::cc == 1) st.push_back(y);
    if (invalid == 0) ed.push_back(y);
    for (int x = 0; x < m; ++x) if (choose[x]) {
      if (dsu::cc == 1 || (dsu::cc == 2 && dsu::root(a[x]) != dsu::root(b[x]))) graph[x][y] = 1;
      if (invalid == 0 || (invalid == 1 && cnt[id[x]] + 1 == bound[id[x]])) graph[y][x] = 1;
    }
  }
  if (st.empty() || ed.empty()) return false;
  std::vector<pii> dist(m, {inf, inf});
  std::vector<int> from(m, -1), mark(m, 0);
  std::queue<int> queue;
  for (auto &x: st) {
    dist[x] = {-w[x], 0};
    queue.push(x);
    mark[x] = true;
  }
  while (!queue.empty()) {
    int u = queue.front(); queue.pop();
    mark[u] = false;
    for (int v = 0; v < m; ++v) if (graph[u][v]) {
      auto cost = dist[u] + pii(choose[v] ? w[v] : -w[v], 1);
      if (dist[v] > cost) {
        dist[v] = cost;
        from[v] = u;
        if (!mark[v]) queue.push(v);
        mark[v] = true;
      }
    }
  }
  int best = -1;
  for (auto &x: ed) if (dist[x].first != inf) {
    if (best == -1 || dist[x] < dist[best]) best = x;
  }
  for (int x = best; x != -1; x = from[x]) {
    choose[x] ^= 1;
  }
  return best != -1;
}
int run(int n, std::vector<int> &bound) {
  int ret = 0;
  while (aug(n, bound)) ++ret;
  return ret;
}
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    n++;
    std::vector<int> bound(m);
    matroid::init();
    int cnt = 0, ret = 0;
    for (int i = 0, c; i < m; ++i) {
      scanf("%d%d", &c, &bound[i]);
      cnt += bound[i]; ret += c;
      for (int j = 0; j < c; ++j) {
        int l, r, w;
        scanf("%d%d%d", &l, &r, &w);
        matroid::add_edge(l - 1, r, w, i);
      }
    }
    for (; ret > cnt; --ret) {
      if (!matroid::aug(n, bound)) break;
    }
    if (ret != cnt) puts("-1");
    else {
      dsu::init(n);
      ret = 0;
      for (int i = 0; i < matroid::m; ++i) {
        if (!matroid::choose[i]) {
          dsu::merge(matroid::a[i], matroid::b[i], matroid::id[i]);
          ret += matroid::w[i];
        }
      }
      if (dsu::cc != 1) ret = -1;
      printf("%d\n", ret);
    }
  }
  return 0;
}

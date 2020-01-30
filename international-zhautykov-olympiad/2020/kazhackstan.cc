#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>

const int N = 1e5 + 10;
using pii = std::pair<int, int>;
using ppp = std::pair<pii, pii>;

void upd(ppp &x, pii y) {
  if (y > x.first) std::swap(x.first, y);
  if (y.second == x.first.second) return;
  if (y > x.second || x.first.second == x.second.second) x.second = y;
}

void upd(ppp &x, const ppp &y) {
  upd(x, y.first);
  upd(x, y.second);
}

struct SegmentTree {
  std::vector<ppp> u;
  std::vector<int> indices;
  std::vector<pii> dist;
  int n;
  void add(int id, pii d) {
    indices.push_back(id);
    dist.push_back(d);
  }
  void init() {
    n = indices.size();
    u.assign(n * 2, {{-2, -2}, {-2, -2}});
    for (int i = 0; i < n; ++i) u[i + n] = {dist[i], {-2, -2}};
    for (int i = n - 1; i > 0; --i) {
      u[i] = u[i * 2];
      upd(u[i], u[i * 2 + 1]);
    }
  }
  ppp query(int l, int r) { // [l, r]
    ppp ret = {{-2, -2}, {-2, -2}};
    l = std::lower_bound(indices.begin(), indices.end(), l) - indices.begin();
    r = std::upper_bound(indices.begin(), indices.end(), r) - indices.begin();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) upd(ret, u[l++]);
      if (r & 1) upd(ret, u[--r]);
    }
    return ret;
  }
};

struct CentroidNode {
  std::vector<pii> child;
  std::vector<int> dist_cnt;
  std::vector<std::vector<int>> child_dist_cnt;
  SegmentTree tree;

  void init() {
    for (size_t i = 1; i < dist_cnt.size(); ++i) {
      dist_cnt[i] += dist_cnt[i - 1];
    }
    for (auto &dist_cnt: child_dist_cnt) {
      for (size_t i = 1; i < dist_cnt.size(); ++i) {
        dist_cnt[i] += dist_cnt[i - 1];
      }
    }
    tree.init();
  }
} cns[N];

struct Entry {
  int root;
  int dist;
  Entry(int root, int dist): root(root), dist(dist) {}
};

std::vector<Entry> entries[N];
std::vector<int> edges[N];
int n, q;

namespace centroid {
  int size[N], mark[N], dist[N];
  int belong[N];
  int total, mins, root;

  void init(int n) {
    for (int i = 0; i < n; ++i) mark[i] = 0;
  }
  void get_centroid(int u, int p = -1) {
    int mx = 0; size[u] = 1;
    for (auto &v: edges[u]) if (v != p && !mark[v]) {
      get_centroid(v, u);
      size[u] += size[v];
      mx = std::max(mx, size[v]);
    }
    mx = std::max(mx, total - size[u]);
    if (mx < mins) mins = mx, root = u;
  }

  void add_dist(std::vector<int> &cnt, int d) {
    while (cnt.size() <= d) cnt.push_back(0);
    cnt[d]++;
  }

  void get_dist(int u, int p, int dist, int id) {
    entries[u].emplace_back(root, dist);
    belong[u] = id;
    add_dist(cns[root].dist_cnt, dist);
    add_dist(cns[root].child_dist_cnt[id], dist);
    for (auto &v: edges[u]) if (v != p && !mark[v]) {
      get_dist(v, u, dist + 1, id);
    }
  }

  int work(int u, int tot) {
    total = tot; mins = tot * 2;
    get_centroid(u);
    mark[u = root] = 1;
    get_centroid(u);
    entries[u].emplace_back(u, 0);
    add_dist(cns[u].dist_cnt, 0);
    int id = 0;
    for (auto &v: edges[u]) if (!mark[v]) {
      cns[u].child_dist_cnt.emplace_back();
      get_dist(v, u, 1, id++);
    }
    for (auto &v: edges[u]) if (!mark[v]) {
      auto rv = work(v, size[v]);
      cns[u].child.emplace_back(v, rv);
    }
    return u;
  }

  void ins(int id, int v, int t) {
    int index = -1;
    for (int i = entries[v].size() - 1; i >= 0; --i) {
      cns[entries[v][i].root].tree.add(id, {t + entries[v][i].dist, index});
      //printf("ins v=%d id=%d root=%d dist=%d index=%d\n", v, id, entries[v][i].root, t + entries[v][i].dist, index);
      index = belong[entries[v][i].root];
    }
  }

  int count(int root, int bound, int idx) {
    if (bound < 0) return 0;
    int ret = 0;
    if (bound < cns[root].dist_cnt.size()) ret += cns[root].dist_cnt[bound];
    else ret += cns[root].dist_cnt.back();
    if (idx != -1) {
      const auto &dist_cnt = cns[root].child_dist_cnt[idx];
      if (bound < dist_cnt.size()) ret -= dist_cnt[bound];
      else ret -= dist_cnt.back();
    }
    return ret;
  }
  int solve(int l, int r, int t, int root, int level, std::vector<pii> ups) {
    auto p = cns[root].tree.query(l, r);
    /*printf("solve l=%d r=%d t=%d lev=%d root=%d ups=", l, r, t, level, root);
    for (auto e: ups) printf("{%d %d}, ", e.first, e.second);
    puts("");
    printf("{{%d %d}, {%d %d}}\n", p.first.first, p.first.second, p.second.first, p.second.second);*/
    for (auto &e: ups) {
      int dist = e.second + entries[e.first][level].dist;
      int index = level + 1 == entries[e.first].size() ? -1 : belong[entries[e.first][level + 1].root];
      upd(p, {dist, index});
    }
    //printf("{{%d %d}, {%d %d}}\n", p.first.first, p.first.second, p.second.first, p.second.second);
    int ret = count(root, t - p.first.first, p.first.second);
    if (p.first.second != -1) {
      int go = cns[root].child[p.first.second].second;
      int best = p.second.first;
      std::vector<pii> t_ups;
      for (auto &e: ups) {
        if (level + 1 == entries[e.first].size() || entries[e.first][level + 1].root != go) {
          best = std::max(best, e.second + entries[e.first][level].dist);
        } else {
          t_ups.push_back(e);
        }
      }
      if (best != -2) {
        t_ups.emplace_back(cns[root].child[p.first.second].first, best + 1);
      }
      ret += solve(l, r, t, go, level + 1, t_ups);
    }
    return ret;
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  centroid::init(n);
  int root = centroid::work(0, n);
  int m = 0;
  std::vector<int> ql, qr, qt;
  for (int i = 0; i < q; ++i) {
    int type, t, l, r, v;
    scanf("%d", &type);
    if (type == 1) {
      scanf("%d%d", &v, &t);
      centroid::ins(m++, v - 1, t);
    } else {
      scanf("%d%d%d", &l, &r, &t);
      ql.push_back(l - 1);
      qr.push_back(r - 1);
      qt.push_back(t);
    }
  }

  for (int i = 0; i < n; ++i) cns[i].init();
  for (size_t i = 0; i < ql.size(); ++i) {
    int ret = centroid::solve(ql[i], qr[i], qt[i], root, 0, {});
    printf("%d\n", ret);
  }
  return 0;
}

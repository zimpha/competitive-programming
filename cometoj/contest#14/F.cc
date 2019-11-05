#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

struct SegmentTree {
  std::vector<int> ref[N * 2], dsu[N * 2];
  int n;
  void build() {
    for (int i = 0; i < n * 2; ++i) if (!ref[i].empty()) {
      int m = ref[i].size();
      dsu[i].resize(m + 1);
      for (int j = 0; j <= m; ++j) dsu[i][j] = j;
    }
  }
  int root(int i, int x) {
    if (dsu[i][x] != x) dsu[i][x] = root(i, dsu[i][x]);
    return dsu[i][x];
  }
  void remove(int i, int p) { dsu[i][p] = p + 1; }
  int retrieve(int i, int bound) {
    if (ref[i].empty()) return -1;
    int p = root(i, bound);
    if (p == (int)ref[i].size()) return -1;
    else return ref[i][p];
  }
  void erase(const std::vector<int>& indices, int l, int r) {
    int i = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) remove(l++, indices[i++]);
      if (r & 1) remove(--r, indices[i++]);
    }
  }
  std::vector<int> insert(int l, int r, int label) {
    static int indices[30];
    int m = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        indices[m++] = ref[l].size();
        ref[l++].push_back(label);
      }
      if (r & 1) {
        ref[--r].push_back(label);
        indices[m++] = ref[r].size() - 1;
      }
    }
    return {indices, indices + m};
  }
} st_hor, st_ver;

struct Segment {
  std::vector<int> indices;
  std::vector<int> bounds;
  int l, r;
  int dfn, low;
} segs[N * 2];

bool mark[N * 2];
std::vector<int> ver[N], hor[N];
std::vector<int> depth[N * 2];
int parent[N * 2], out[N * 2];
int n;

void dfs(int x, int dep) {
  out[x] = dep > 1;
  segs[x].dfn = segs[x].low = dep;
  if (x < n) st_ver.erase(segs[x].indices, segs[x].l, segs[x].r);
  else st_hor.erase(segs[x].indices, segs[x].l, segs[x].r);
  depth[dep].push_back(x);
  auto &st = x < n ? st_hor : st_ver;
  for (int u = x % n + n, i = 0; u > 1; ) {
    auto y = st.retrieve(u, segs[x].bounds[i]);
    if (y == -1 || y % n >= segs[x].r) u >>= 1, ++i;
    else parent[y] = x, dfs(y, dep + 1);
  }
}

int main() {
  scanf("%d", &n);
  st_hor.n = st_ver.n = n;
  for (int i = 0; i < n * 2; ++i) {
    scanf("%d%d", &segs[i].l, &segs[i].r);
    --segs[i].l;
    segs[i].dfn = segs[i].low = 0;
    if (i < n) hor[segs[i].l].push_back(i);
    else ver[segs[i].l].push_back(i);
  }
  for (int i = 0; i < n * 2; ++i) {
    auto& st = i < n ? st_ver : st_hor;
    auto& sets = i < n ? ver[i] : hor[i - n];
    for (auto &j: sets) {
      static int bounds[30];
      int m = 0;
      for (int u = j % n + n; u > 0; u >>= 1) {
        bounds[m++] = st.ref[u].size();
      }
      segs[j].bounds = {bounds, bounds + m};
    }
    segs[i].indices = st.insert(segs[i].l, segs[i].r, i);
  }
  st_ver.build(); st_hor.build();
  for (int i = 0; i < n * 2; ++i) if (!segs[i].dfn) {
    dfs(i, 1);
  }
  st_ver.build(); st_hor.build();
  std::vector<bool> removed(n * 2);
  for (int d = 1; d <= n * 2; ++d) {
    if (depth[d].empty()) break;
    for (auto &u: depth[d]) if (!removed[u]) {
      removed[u] = 1;
      if (u < n) st_ver.erase(segs[u].indices, segs[u].l, segs[u].r);
      else st_hor.erase(segs[u].indices, segs[u].l, segs[u].r);
    }
    for (auto &x: depth[d]) {
      auto &st = x < n ? st_hor : st_ver;
      for (int u = x % n + n, i = 0; u > 0; ) {
        auto y = st.retrieve(u, segs[x].bounds[i]);
        if (y == -1 || y % n >= segs[x].r) u >>= 1, ++i;
        else {
          removed[y] = 1;
          st.erase(segs[y].indices, segs[y].l, segs[y].r);
          if (parent[y] != x) segs[y].low = d;
        }
      }
    }
  }
  for (int d = n * 2; d >= 2; --d) {
    for (auto &x: depth[d]) {
      segs[parent[x]].low = std::min(segs[parent[x]].low, segs[x].low);
      if (segs[x].low >= segs[parent[x]].dfn) {
        if (++out[parent[x]] == 2) mark[parent[x]] = 1;
      }
    }
  }
  for (int i = 0; i < n; ++i) putchar(mark[i] + '0');
  puts("");
  for (int i = 0; i < n; ++i) putchar(mark[i + n] + '0');
  puts("");
  return 0;
}

#include <cstdio>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <algorithm>

using i64 = long long;

const int N = 1e5 + 10, V = N * 3 * 2;
const int M = V * 20;

int ls[M], rs[M], dis[M], size;
int row_rt[N], col_rt[N];
std::pair<int, int> ban[N];
std::vector<int> edges[V];
int label[V], vl[V], vr[V], vp[V], cnt;
std::unordered_map<int, int> label2cnt;
int n, m;

i64 id(int x, int y) { return (i64)x * n + y; }

int ins(int o, int l, int r, int x, int &label) {
  int p = size++;
  ls[p] = ls[o];
  rs[p] = rs[o];
  if (l + 1 == r) return label = p;
  int m = (l + r) >> 1;
  if (x < m) ls[p] = ins(ls[o], l, m, x, label);
  else rs[p] = ins(rs[o], m, r, x, label);
  return p;
}

void get(int o, int l, int r, int L, int R, std::vector<int> &vs) {
  if (!o) return;
  if (L <= l && R >= r) {
    vs.push_back(o);
    return;
  }
  int m = (l + r) >> 1;
  if (L < m) get(ls[o], l, m, L, R, vs);
  if (R > m) get(rs[o], m, r, L, R, vs);
}

int build(int* root) {
  std::sort(ban, ban + m);
  std::vector<std::vector<int>> add(n + 1), sub(n + 1);
  for (int x = 0, i = 0, j; x < n; ++x) {
    for (j = i; j < m && ban[j].first == x; ++j);
    int last = -1;
    for (; i < j; ++i) {
      if (last + 1 != ban[i].second) {
        add[last + 1].push_back(x);
        sub[ban[i].second].push_back(x);
      }
      last = ban[i].second;
    }
    if (last + 1 != n) {
      add[last + 1].push_back(x);
      sub[n].push_back(x);
    }
  }
  std::vector<int> last(n, -1);
  for (int y = 0; y <= n; ++y) {
    if (y) root[y] = root[y - 1];
    for (auto &x: sub[y]) {
      assert(last[x] != -1);
      if (y != n) {
        root[y] = ins(root[y], 0, n, x, label[cnt]);
      }
      vr[last[x]] = y;
      last[x] = -1;
    }
    for (auto &x: add[y]) {
      assert(last[x] == -1);
      root[y] = ins(root[y], 0, n, x, label[cnt]);
      label2cnt[label[cnt]] = cnt;
      vp[cnt] = x;
      vl[cnt] = y;
      last[x] = cnt++;
    }
  }
  return cnt;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0, x, y; i < m; ++i) {
    scanf("%d%d", &y, &x);
    --x, --y;
    ban[i] = {x, y};
  }
  size = 1;
  cnt = 0;
  int row_segs = build(col_rt);
  for (int i = 0; i < m; ++i) {
    std::swap(ban[i].first, ban[i].second);
  }
  build(row_rt);
  for (int i = 0; i < row_segs; ++i) {
    //printf("x=%d yl=%d yr=%d\n", vp[i], vl[i], vr[i]);
    get(row_rt[vp[i]], 0, n, vl[i], vr[i], edges[i]);
  }
  for (int i = row_segs; i < cnt; ++i) {
    //printf("y=%d xl=%d xr=%d\n", vp[i], vl[i], vr[i]);
    get(col_rt[vp[i]], 0, n, vl[i], vr[i], edges[i]);
  }
  for (int i = 0; i < size; ++i) dis[i] = -1;
  std::vector<int> queue = {label[0]};
  dis[label[0]] = 0;
  while (!queue.empty()) {
    std::vector<int> buffer;
    for (auto &u: queue) if (label2cnt.count(u)) {
      for (auto &v: edges[label2cnt[u]]) {
        if (dis[v] == -1) {
          dis[v] = dis[u] + 1;
          buffer.push_back(v);
        }
      }
    }
    for (size_t i = 0; i < buffer.size(); ++i) {
      int u = buffer[i];
      if (ls[u] && dis[ls[u]] == -1) {
        dis[ls[u]] = dis[u];
        buffer.push_back(ls[u]);
      }
      if (rs[u] && dis[rs[u]] == -1) {
        dis[rs[u]] = dis[u];
        buffer.push_back(rs[u]);
      }
    }
    queue.clear();
    for (auto &v: buffer) {
      if (!ls[v] && !rs[v]) queue.push_back(v);
    }
  }
  i64 ret = 0, cells = 0;
  for (int i = 0; i < cnt; ++i) {
    //printf("dis=%d\n", dis[label[i]]);
    if (dis[label[i]] == -1) continue;
    ret += i64(vr[i] - vl[i]) * dis[label[i]];
    cells += vr[i] - vl[i];
  }
  printf("%lld\n", (ret - cells / 2) / 2);
  return 0;
}

#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

using int64 = long long;
using int128 = __int128;

const int N = 1e5 + 10, S = N << 2;
const int128 inf = int128(1) << 100;

int n, q, k, dim;

struct node {
  node *ls, *rs;
  int64 d[5], mi[5], mx[5];
  void init() {
    for (int i = 0; i < k; ++i) {
      mi[i] = mx[i] = d[i];
    }
  }
  bool operator < (const node &rhs) const {
    return d[dim] < rhs.d[dim];
  }
  void update() {
    for (int i = 0; i < k; ++i) {
      if (ls) mi[i] = std::min(mi[i], ls->mi[i]);
      if (ls) mx[i] = std::max(mx[i], ls->mx[i]);
      if (rs) mi[i] = std::min(mi[i], rs->mi[i]);
      if (rs) mx[i] = std::max(mx[i], rs->mx[i]);
    }
  }
} tree[N], ask;
int128 best;

inline int128 sqr(int64 x) {return (int128)x * x;}

node* build(int l, int r, int dep) {
  if (l >= r) return NULL;
  int mid = (l + r) >> 1; 
  dim = dep % k;
  std::nth_element(tree + l, tree + mid, tree + r);
  tree[mid].init();
  tree[mid].ls = build(l, mid, dep + 1);
  tree[mid].rs = build(mid + 1, r, dep + 1);
  tree[mid].update();
  return tree + mid;
}

void query(node *o) {
  if (!o) return;
  auto partition = [&](node *o) {
    int128 ret = 0;
    for (int i = 0; i < k; ++i) {
      if (ask.d[i] > o->mx[i]) ret += sqr(o->mx[i] - ask.d[i]);
      if (ask.d[i] < o->mi[i]) ret += sqr(o->mi[i] - ask.d[i]);
    }
    return ret;
  };
  int128 dl = o->ls ? partition(o->ls) : inf;
  int128 dr = o->rs ? partition(o->rs) : inf;
  int128 tmp = 0;
  for (int i = 0; i < k; ++i) {
    tmp += sqr(ask.d[i] - o->d[i]);
  }
  if (best == -1 || tmp < best) best = tmp;
  if (dl < dr) {
    if (best == -1 || dl < best) query(o->ls);
    if (best == -1 || dr < best) query(o->rs);
  } else {
    if (best == -1 || dr < best) query(o->rs);
    if (best == -1 || dl < best) query(o->ls);
  }
}

int main() {
  scanf("%d%d%d", &n, &k, &q);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) {
      scanf("%lld", &tree[i].d[j]);
    }
  }
  node *root = build(0, n, 0);
  for (int it = 0; it < q; ++it) {
    for (int i = 0; i < k; ++i) {
      scanf("%lld", &ask.d[i]);
    }
    best = -1;
    query(root);
    constexpr int64 base = 1000000000000000000;
    if (best < base) printf("%lld\n", int64(best));
    else printf("%lld%019lld\n", int64(best / base), int64(best % base));
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <cassert>
#include <set>
#include <algorithm>

using i64 = long long;

const int N = 1e5 + 10;
const i64 inf = i64(1) << 60;

namespace seg {
struct Node {
  int l, r;
  i64 val;
} pool[N * 17 * 17 * 2];
int sz;

void init() {
  sz = 0;
}

int alloc() {
  pool[sz].l = pool[sz].r = -1;
  pool[sz].val = 0;
  return sz++;
}

int add(int o, int l, int r, int x, i64 delta) {
  int p = alloc();
  if (o != -1) pool[p] = pool[o];
  if (l + 1 == r) {
    pool[p].val += delta;
  } else {
    int m = (l + r) >> 1;
    if (x < m) pool[p].l = add(pool[p].l, l, m, x, delta);
    else pool[p].r = add(pool[p].r, m, r, x, delta);
    pool[p].val = -inf;
    if (pool[p].l != -1) pool[p].val = std::max(pool[p].val, pool[pool[p].l].val);
    if (pool[p].r != -1) pool[p].val = std::max(pool[p].val, pool[pool[p].r].val);
  }
  return p;
}

std::pair<i64, int> lower(int o, int l, int r, int pos) {
  if (o == -1) return {-inf, -1};
  if (l + 1 == r) return {pool[o].val, l};
  int m = (l + r) >> 1;
  std::pair<i64, int> ret = {-inf, -1};
  if (pool[o].r != -1 && m <= pos) ret = lower(pool[o].r, m, r, pos);
  if (ret.second == -1 && pool[o].l != -1) ret = lower(pool[o].l, l, m, pos);
  return ret;
}

i64 get(int o, int l, int r, int L, int R) {
  if (o == -1) return -inf;
  if (L <= l && r <= R) return pool[o].val;
  int m = (l + r) >> 1;
  i64 ret = -inf;
  if (L < m) ret = std::max(ret, get(pool[o].l, l, m, L, R));
  if (R > m) ret = std::max(ret, get(pool[o].r, m, r, L, R));
  return ret;
}

}

int roots[N << 2];
int n, q;

std::pair<i64, i64> add(int o, int l, int r, int x, int y1, int y2, i64 delta) {
  if (l + 1 == r) {
    auto val = seg::lower(roots[o], 0, n, y1);
    if (val.second != y1) {
      roots[o] = seg::add(roots[o], 0, n, y1, val.first);
    }
    if (y2 != n && seg::lower(roots[o], 0, n, y2).second != y2) {
      roots[o] = seg::add(roots[o], 0, n, y2, val.first);
    }
    roots[o] = seg::add(roots[o], 0, n, y1, delta);
    return {val.first, val.first + delta};
  }
  int m = (l + r) >> 1;
  std::pair<i64, i64> val;
  i64 w;
  if (x < m) {
    val = add(o << 1, l, m, x, y1, y2, delta);
    if (val.first == val.second) return val;
    w = seg::lower(roots[o << 1 | 1], 0, n, y1).first;
  } else {
    val = add(o << 1 | 1, m, r, x, y1, y2, delta);
    if (val.first == val.second) return val;
    w = seg::lower(roots[o << 1], 0, n, y1).first;
  }
  val.first = std::max(val.first, w);
  val.second = std::max(val.second, w);
  if (val.first == val.second) return val;
  auto t_val = seg::lower(roots[o], 0, n, y1);
  if (t_val.second != y1) {
    roots[o] = seg::add(roots[o], 0, n, y1, t_val.first);
  }
  if (y2 != n && seg::lower(roots[o], 0, n, y2).second != y2) {
    roots[o] = seg::add(roots[o], 0, n, y2, t_val.first);
  }
  roots[o] = seg::add(roots[o], 0, n, y1, val.second - val.first);
  return val;
}

i64 query(int o, int l, int r, int x1, int x2, int y1, int y2) {
  if (roots[o] == -1) return -inf;
  if (x1 <= l && r <= x2) {
    return std::max(
      seg::lower(roots[o], 0, n, y1).first,
      seg::get(roots[o], 0, n, y1, y2)
    );
  }
  int m = (l + r) >> 1;
  i64 ret = -inf;
  if (x1 < m) ret = std::max(ret, query(o << 1, l, m, x1, x2, y1, y2));
  if (x2 > m) ret = std::max(ret, query(o << 1 | 1, m, r, x1, x2, y1, y2));
  return ret;
}

int get(int o, int l, int r, int x) {
  if (l + 1 == r) return roots[o];
  int m = (l + r) >> 1;
  if (x < m) return get(o << 1, l, m, x);
  else return get(o << 1 | 1, m, r, x);
}

void set(int o, int l, int r, int x, int root) {
  if (roots[o] == -1) roots[o] = root;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  if (x < m) return set(o << 1, l, m, x, root);
  else return set(o << 1 | 1, m, r, x, root);
}

int main() {
  scanf("%d%d", &n, &q);
  memset(roots, -1, sizeof(roots));
  int t_root = seg::add(-1, 0, n, 0, -inf);
  set(1, 0, n, 0, t_root);
  set(1, 0, n, n - 1, t_root);
  add(1, 0, n, 0, 0, n, inf);
  add(1, 0, n, n - 1, 0, n, inf);
  std::set<int> ver = {0, n}, hor = {0, n};
  for (int i = 0; i < q; ++i) {
    int op, a, b, c, d;
    scanf("%d%d%d", &op, &a, &b);
    if (op == 1) {
      if (a == 0) {
        auto it = ver.upper_bound(b);
        int x = *(--it);
        if (x != b) {
          int t_root = get(1, 0, n, x);
          set(1, 0, n, b - 1, t_root);
          set(1, 0, n, b, t_root);
        }
      }
      if (a == 0) ver.insert(b);
      else hor.insert(b);
    } else if (op == 2) {
      scanf("%d", &c);
      --a, --b;
      auto v_it = ver.upper_bound(a), h_it = hor.upper_bound(b);
      int x2 = *v_it, y2 = *h_it;
      int x1 = *(--v_it), y1 = *(--h_it);
      add(1, 0, n, x1, y1, y2, c);
      if (x1 != x2 - 1) {
        add(1, 0, n, x2 - 1, y1, y2, c);
      }
    } else if (op == 3) {
      scanf("%d%d", &c, &d);
      --a, --b;
      a = *(--ver.upper_bound(a));
      b = *(--hor.upper_bound(b));
      printf("%lld\n", query(1, 0, n, a, c, b, d));
    }
  }
  return 0;
}

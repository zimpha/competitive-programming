#include <cstdio>

using int64 = long long;

const int N = 800000 + 10;

struct Node {
  int64 dp, add;
  int mh, th;
  void set_dp(int64 v) {
    dp += v;
    add += v;
  }
  void set_h(int v) {
    mh = v;
    th = v;
  }
} tree[N << 2];

void push(int o) {
  if (tree[o].add) {
    tree[o << 1].set_dp(tree[o].add);
    tree[o << 1 | 1].set_dp(tree[o].add);
    tree[o].add = 0;
  }
  if (tree[o].th) {
    tree[o << 1].set_h(tree[o].th);
    tree[o << 1 | 1].set_h(tree[o].th);
    tree[o].th = 0;
  }
}

void update(int o) {
  tree[o].dp = std::min(tree[o << 1].dp, tree[o << 1 | 1].dp);
  tree[o].mh = std::max(tree[o << 1].mh, tree[o << 1 | 1].mh);
}

void add(int o, int l, int r, int L, int R, int64 v) {
  if (L <= l && R >= r) {
    tree[o].set_dp(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R, v);
  if (R > m) add(o << 1 | 1, m, r, L, R, v);
  update(o);
}

void set_h(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    tree[o].set_h(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) set_h(o << 1, l, m, L, R, v);
  if (R > m) set_h(o << 1 | 1, m, r, L, R, v);
  update(o);
}

// find left position mh <= x
int query(int o, int l, int r, int L, int R, int x) {
  if (l + 1 == r) return l;
}

int main() {
  return 0;
}

#include <cassert>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <utility>
#include <functional>

namespace Treap {
struct node_t {
  node_t *l, *r;
  int size, value;
  node_t(int v): l(0), r(0), size(1), value(v) {}
  node_t* update() {
    size = 1;
    if (l) size += l->size;
    if (r) size += r->size;
    return this;
  }
};

int get_size(node_t *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

std::pair<node_t*, node_t*> split_by_value(node_t *o, int v) {//[-inf, v), [v, +inf)
  node_t *l = 0, *r = 0;
  if (!o) return {l, r};
  if (o->value < v) {
    std::tie(o->r, r) = split_by_value(o->r, v);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_value(o->l, v);
    r = o;
  }
  o->update();
  return {l, r};
}

std::pair<node_t*, node_t*> split_by_size(node_t *o, int size) {//[0, size), [size, +inf)
  node_t *l = 0, *r = 0;
  if (!o) return {l, r};
  int ls = get_size(o->l);
  if (ls < size) {
    std::tie(o->r, r) = split_by_size(o->r, size - ls - 1);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_size(o->l, size);
    r = o;
  }
  o->update();
  return {l, r};
}

node_t* merge(node_t *l, node_t *r) {
  if (!l || !r) return l ? l : r;
  if (random(l->size, r->size)) {
    l->r = merge(l->r, r);
    return l->update();
  } else {
    r->l = merge(l, r->l);
    return r->update();
  }
}

int rank(node_t *o, int v) {// number elements < v
  if (!o) return 0;
  if (o->value >= v) return rank(o->l, v);
  else return get_size(o->l) + 1 + rank(o->r, v);
}

node_t* kth(node_t *o, int k) {
  int cnt = get_size(o->l);
  if (cnt + 1 == k) return o;
  if (k <= cnt) return kth(o->l, k);
  else return kth(o->r, k - cnt - 1);
}
}

struct node {
  node *ls, *rs;
  Treap::node_t *rt;
  node(): ls(0), rs(0), rt(0) {}
  void insert(int v) {
    Treap::node_t *a, *b, *p = new Treap::node_t(v);
    std::tie(a, b) = Treap::split_by_value(rt, v);
    rt = Treap::merge(a, Treap::merge(p, b));
  }
  void remove(int v) {
    Treap::node_t *a, *b, *c;
    std::tie(a, b) = Treap::split_by_value(rt, v);
    std::tie(b, c) = Treap::split_by_value(b, v + 1);
    assert(b->size == 1);
    rt = Treap::merge(a, c);
  }
  int rank(int v) { // < v
    return Treap::rank(rt, v);
  }
  int count(int a, int b) {// [a, b]
    return rank(b + 1) - rank(a);
  }
};

node* insert(node *rt, int l, int r, int x, int v) {
  if (!rt) rt = new node();
  rt->insert(v);
  if (l == r) return rt;
  int m = (l + r) >> 1;
  if (x <= m) rt->ls = insert(rt->ls, l, m, x, v);
  else rt->rs = insert(rt->rs, m + 1, r, x, v);
  return rt;
}

node* remove(node *rt, int l, int r, int x, int v) {
  rt->remove(v);
  if (l == r) return rt;
  int m = (l + r) >> 1;
  if (x <= m) rt->ls = remove(rt->ls, l, m, x, v);
  else rt->rs = remove(rt->rs, m + 1, r, x, v);
  return rt;
}

int rank(node *o, int l, int r, int x, int a, int b) {
  if (!o) return 0;
  int m = (l + r) >> 1;
  if (x <= m) return rank(o->ls, l, m, x, a, b);
  else return rank(o->rs, m + 1, r, x, a, b) + (o->ls ? o->ls->count(a, b) : 0);
}

int kth(node *o, int l, int r, int x, int a, int b) {
  if (l == r) return l;
  int size = o->ls ? o->ls->count(a, b) : 0;
  int m = (l + r) >> 1;
  if (x <= size) return kth(o->ls, l, m, x, a, b);
  else return kth(o->rs, m + 1, r, x - size, a, b);
}

int pred(node *o, int l, int r, int x, int a, int b) {
  if (!o || o->count(a, b) == 0) return -1e9;
  if (l == r) return l;
  int m = (l + r) >> 1;
  if (x <= m) return pred(o->ls, l, m, x, a, b);
  else {
    int v = pred(o->rs, m + 1, r, x, a, b);
    if (v == -1e9) v = pred(o->ls, l, m, x, a, b);
    return v;
  }
}

int succ(node *o, int l, int r, int x, int a, int b) {
  if (!o || o->count(a, b) == 0) return -1e9;
  if (l == r) return l;
  int m = (l + r) >> 1;
  if (x > m) return succ(o->rs, m + 1, r, x, a, b);
  else {
    int v = succ(o->ls, l, m, x, a, b);
    if (v == -1e9) v = succ(o->rs, m + 1, r, x, a, b);
    return v;
  }
}

int main() {
  const int U = 1e8;
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n);
  node *rt = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i - 1]);
    rt = insert(rt, -U, U, a[i - 1], i);
  }
  for (int i = 0; i < m; ++i) {
    int op, l, r, x;
    scanf("%d%d", &op, &l);
    if (op != 3) scanf("%d%d", &r, &x);
    else scanf("%d", &x);
    if (op == 1) {
      printf("%d\n", rank(rt, -U, U, x, l, r) + 1);
    } else if (op == 2) {
      printf("%d\n", kth(rt, -U, U, x, l, r));
    } else if (op == 3) {
      rt = remove(rt, -U, U, a[l - 1], l);
      a[l - 1] = x;
      rt = insert(rt, -U, U, a[l - 1], l);
    } else if (op == 4) {
      printf("%d\n", pred(rt, -U, U, x - 1, l, r));
    } else if (op == 5) {
      printf("%d\n", succ(rt, -U, U, x + 1, l, r));
    }
  }
  return 0;
}

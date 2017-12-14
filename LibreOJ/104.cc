#include <cstdio>
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

int main() {
  int n;
  scanf("%d", &n);
  Treap::node_t *rt = 0;
  for (int i = 0; i < n; ++i) {
    int op, x;
    scanf("%d%d", &op, &x);
    if (op == 1) {
      Treap::node_t *p = new Treap::node_t(x), *a, *b;
      std::tie(a, b) = Treap::split_by_value(rt, x);
      rt = Treap::merge(a, Treap::merge(p, b));
    } else if (op == 2) {
      Treap::node_t *a, *b, *c;
      std::tie(a, b) = Treap::split_by_value(rt, x);
      std::tie(b, c) = Treap::split_by_size(b, 1);
      rt = Treap::merge(a, c);
    } else if (op == 3) {
      printf("%d\n", Treap::rank(rt, x) + 1);
    } else if (op == 4) {
      printf("%d\n", Treap::kth(rt, x)->value);
    } else if (op == 5) {
      Treap::node_t *a, *b, *c;
      std::tie(a, b) = Treap::split_by_value(rt, x);
      std::tie(a, c) = Treap::split_by_size(a, a->size - 1);
      printf("%d\n", c->value);
      rt = Treap::merge(a, Treap::merge(c, b));
    } else {
      Treap::node_t *a, *b, *c;
      std::tie(a, b) = Treap::split_by_value(rt, x + 1);
      std::tie(b, c) = Treap::split_by_size(b, 1);
      printf("%d\n", b->value);
      rt = Treap::merge(a, Treap::merge(b, c));
    }
  }
}

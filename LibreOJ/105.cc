#include <cstdio>
#include <cstdlib>
#include <utility>
#include <functional>

namespace Treap {
struct node_t {
  node_t *l, *r;
  int size, value;
  bool rev;
  node_t(int v): l(0), r(0), size(1), value(v), rev(0) {}
  node_t* update() {
    size = 1;
    if (l) size += l->size;
    if (r) size += r->size;
    return this;
  }
  void mark() {
    rev ^= 1;
    std::swap(l, r);
  }
  void push() {
    if (rev) {
      if (l) l->mark();
      if (r) r->mark();
      rev = 0;
    }
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
  o->push();
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
  l->push(); r->push();
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
  o->push();
  if (o->value >= v) return rank(o->l, v);
  else return get_size(o->l) + 1 + rank(o->r, v);
}

node_t* kth(node_t *o, int k) {
  o->push();
  int cnt = get_size(o->l);
  if (cnt + 1 == k) return o;
  if (k <= cnt) return kth(o->l, k);
  else return kth(o->r, k - cnt - 1);
}

void print(node_t *o) {
  if (!o) return;
  o->push();
  print(o->l);
  printf("%d ", o->value);
  print(o->r);
}
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  Treap::node_t *rt = 0;
  for (int i = 0; i < n; ++i) {
    Treap::node_t *p = new Treap::node_t(i + 1);
    rt = Treap::merge(rt, p);
  }
  for (int i = 0; i < m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    Treap::node_t *a, *b, *c;
    std::tie(b, c) = Treap::split_by_size(rt, r);
    std::tie(a, b) = Treap::split_by_size(b, l - 1);
    b->mark();
    rt = Treap::merge(a, Treap::merge(b, c));
  }
  print(rt);
  return 0;
}

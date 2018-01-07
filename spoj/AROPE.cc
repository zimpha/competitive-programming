#include <cstdio>
#include <cstdlib>
#include <utility>
#include <functional>

struct node {
  node *l, *r;
  int size;
  char value;
  bool rev;
  node(char v): l(0), r(0), size(1), value(v), rev(0) {}
  void mark() {
    rev ^= 1;
    std::swap(l, r);
  }
  void push() {
    if (rev) {
      if (l) l->mark();
      if (r) r->mark();
    }
    rev = 0;
  }
  node* update() {
    size = 1;
    if (l) size += l->size;
    if (r) size += r->size;
    return this;
  }
};

int get_size(node *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

std::pair<node*, node*> split_by_size(node *o, int size) {//[0, size), [size, +inf)
  node *l = 0, *r = 0;
  if (o) o->push();
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

node* merge(node *l, node *r) {
  if (l) l->push();
  if (r) r->push();
  if (!l || !r) return l ? l : r;
  if (random(l->size, r->size)) {
    l->r = merge(l->r, r);
    return l->update();
  } else {
    r->l = merge(l, r->l);
    return r->update();
  }
}

int rank(node *o, int v) {// number elements < v
  if (!o) return 0;
  o->push();
  if (o->value >= v) return rank(o->l, v);
  else return get_size(o->l) + 1 + rank(o->r, v);
}

node* kth(node *o, int k) {
  if (o) o->push();
  int cnt = get_size(o->l);
  if (cnt + 1 == k) return o;
  if (k <= cnt) return kth(o->l, k);
  else return kth(o->r, k - cnt - 1);
}

const int  N = 1e5 + 10;

char s[N];

int main() {
  scanf("%s", s);
  node *root = 0;
  for (int i = 0; s[i]; ++i) {
    node *p = new node(s[i]);
    root = merge(root, p);
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int op, x, y;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &x, &y);
      node *a, *b, *c;
      std::tie(a, b) = split_by_size(root, x);
      std::tie(b, c) = split_by_size(b, y - x + 1);
      root = merge(b, merge(a, c));
    } else if (op == 2) {
      scanf("%d%d", &x, &y);
      node *a, *b, *c;
      std::tie(a, b) = split_by_size(root, x);
      std::tie(b, c) = split_by_size(b, y - x + 1);
      root = merge(merge(a, c), b);
    } else {
      scanf("%d", &x);
      printf("%c\n", kth(root, x + 1)->value);
    }
  }
  return 0;
}

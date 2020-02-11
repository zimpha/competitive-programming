#include <cstdio>
#include <cstdlib>
#include <vector>
#include <functional>
#include <algorithm>

const int N = 2e5 + 10;

struct Node {
  Node *l, *r;
  int size, value;
  int mx[2], mi[2];
  bool yes;
  Node* update();
} pool[N];

// find first value > v
int ge(Node *o, int v) {
  if (o->r && o->r->mx[0] > v) return ge(o->r, v);
  else if (o->value > v) return o->value;
  else return ge(o->l, v);
}

// find first value < v
int le(Node *o, int v) {
  if (o->l && o->l->mi[0] < v) return le(o->l, v);
  else if (o->value < v) return o->value;
  else return le(o->r, v);
}

Node* Node::update() {
  size = 1, yes = false;
  mi[0] = mx[0] = value;
  mi[1] = 1e9, mx[1] = 0;
  if (l) {
    size += l->size;
    mi[0] = std::min(mi[0], l->mi[0]);
    mx[0] = std::max(mx[0], l->mx[0]);
    yes |= l->yes || value > l->mi[1];
  }
  if (r) {
    size += r->size;
    mi[0] = std::min(mi[0], r->mi[0]);
    mx[0] = std::max(mx[0], r->mx[0]);
    yes |= r->yes || value < r->mx[1]; 
  }
  if (l && r && !yes) {
    yes |= r->mx[0] > l->mi[1];
    yes |= l->mi[0] < r->mx[1];
    yes |= l->mi[0] < value && value < r->mx[0];
  }
  if (yes) return this;
  if (l) {
    mi[1] = std::min(mi[1], l->mi[1]), mx[1] = std::max(mx[1], l->mx[1]);
    if (l->mi[0] < value) {
      mi[1] = std::min(mi[1], value);
      mx[1] = std::max(mx[1], le(l, value));
    }
  }
  if (r) {
    mi[1] = std::min(mi[1], r->mi[1]), mx[1] = std::max(mx[1], r->mx[1]);
    if (r->mx[0] > value) {
      mx[1] = std::max(mx[1], value);
      mi[1] = std::min(mi[1], ge(r, value));
    }
  }
  if (l && r && l->mi[0] < r->mx[0]) {
    mi[1] = std::min(mi[1], ge(r, l->mi[0]));
    mx[1] = std::max(mx[1], le(l, r->mx[0]));
  }
  return this;
}

int get_size(Node *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

std::pair<Node*, Node*> split_by_size(Node *o, int size) {//[0, size), [size, +inf)
  Node *l = 0, *r = 0;
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

Node* merge(Node *l, Node *r) {
  if (!l || !r) return l ? l : r;
  if (random(l->size, r->size)) {
    l->r = merge(l->r, r);
    return l->update();
  } else {
    r->l = merge(l, r->l);
    return r->update();
  }
}

Node* build(int l, int r) {
  if (l > r) return NULL;
  int m = (l + r) >> 1;
  Node* p = pool + m;
  p->l = build(l, m - 1);
  scanf("%d", &p->value);
  p->r = build(m + 1, r);
  return p->update();
}

int main() {
  int n, q;
  scanf("%d", &n);
  auto root = build(0, n - 1);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    if (k != 0 && k != r - l + 1) {
      Node *a, *b, *c, *x, *y;
      std::tie(b, c) = split_by_size(root, r);
      std::tie(a, b) = split_by_size(b, l - 1);
      std::tie(x, y) = split_by_size(b, r - l + 1 - k);
      root = merge(merge(a, y), merge(x, c));
    }
    puts(root->yes ? "YES" : "NO");
  }
  return 0;
}

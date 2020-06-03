#include <cstdio>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <algorithm>

struct Node {
  Node *l, *r, *p;
  int size, val;
  Node* update() {
    size = 1;
    if (l) l->p = this, size += l->size;
    if (r) r->p = this, size += r->size;
    return this;
  }
};

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

int rank(Node *root, Node *o) {
  int size = get_size(o->l) + 1;
  while (o != root) {
    if (o->p->r == o) {
      size += get_size(o->p->l) + 1;
    }
    o = o->p;
  }
  return size;
}

const int N = 2e5 + 10;

Node* pos[N];

Node* build(int l, int r) {
  if (l > r) return NULL;
  int m = (l + r) >> 1;
  Node* p = new Node();
  p->val = m;
  p->l = build(l, m - 1);
  p->r = build(m + 1, r);
  p->update();
  return pos[m] = p;
}

void print(Node* o) {
  if (!o) return;
  print(o->l);
  printf("%d ", o->val);
  print(o->r);
  if (o->l) assert(o->l->p == o);
  if (o->r) assert(o->r->p == o);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  auto root = build(1, n);
  std::vector<int> mi(n), mx(n);
  for (int i = 0; i < n; ++i) {
    mi[i] = mx[i] = i + 1;
  }
  for (int i = 0; i < m; ++i) {
    int x;
    scanf("%d", &x);
    int s = rank(root, pos[x]);
    mi[x - 1] = std::min(mi[x - 1], std::max(s - 1, 1));
    mx[x - 1] = std::max(mx[x - 1], s);
    if (s != 1) {
      Node *a, *b, *c, *d;
      std::tie(a, d) = split_by_size(root, s);
      std::tie(a, c) = split_by_size(a, s - 2);
      std::tie(b, c) = split_by_size(c, 1);
      root = merge(merge(a, c), merge(b, d));
    }
  }
  for (int i = 1; i <= n; ++i) {
    int s = rank(root, pos[i]);
    mi[i - 1] = std::min(mi[i - 1], s);
    mx[i - 1] = std::max(mx[i - 1], s);
    printf("%d %d\n", mi[i - 1], mx[i - 1]);
  }
  return 0;
}

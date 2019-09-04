#include <cstdio>
#include <vector>
#include <cassert>
#include <functional>
#include <algorithm>

struct FastIO {
  static const int S = 655360;
  char buf[S];
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    eof = false;
  }
  inline int nextChar() {
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, in);
    if (pos == len) {eof = true; return -1;}
    return buf[pos++];
  }
  inline int nextUInt() {
    int c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  inline int nextInt() {
    int s = 1, c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    if (c == '-') s = -1, c = nextChar();
    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline void nextString(char *s) {
    int c = nextChar();
    while (c <= 32) c = nextChar();
    for(; c > 32; c = nextChar()) *s++ = c;
    *s = 0;
  }
} io;

namespace treap {
int rank() {
  int rank = 0;
  while (rand() % 2) ++rank;
  return rank;
}

struct Node {
  int val, delta;
  int size, rank;
  Node *l, *r;
  Node(int v = 0): val(v), delta(0), size(1), l(0), r(0) {
    rank = treap::rank();
  }
  void apply(int d) {
    delta += d;
    val += d;
  }
  void push() {
    if (l) l->apply(delta);
    if (r) r->apply(delta);
    delta = 0;
  }
  Node* update() {
    size = 1;
    if (l) size += l->size;
    if (r) size += r->size;
    return this;
  }
};

int get_size(Node *o) {
  return o ? o->size : 0;
}

std::pair<Node*, Node*> split_by_value(Node *o, int v) {//[-inf, v), [v, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  o->push();
  if (o->val < v) {
    std::tie(o->r, r) = split_by_value(o->r, v);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_value(o->l, v);
    r = o;
  }
  o->update();
  return {l, r};
}

std::pair<Node*, Node*> split_by_size(Node *o, int size) {//[0, size], (size, +inf)
  Node *l = 0, *r = 0;
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

Node* merge(Node *x, Node *y) {
  if (!x || !y) return x ? x : y;
  x->push(); y->push();
  if (x->rank < y->rank) {
    y->l = merge(x, y->l);
    y->update();
    return y;
  } else {
    x->r = merge(x->r, y);
    x->update();
    return x;
  }
}

void print(Node *o) {
  if (!o) return;
  o->push();
  print(o->l);
  printf("%d ", o->val);
  print(o->r);
}
}

int size(treap::Node* o) {
  return o ? o->size : 0;
}

int main() {
  int n = io.nextUInt();
  int m = io.nextUInt();
  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) {
    a[i] = io.nextUInt();
  }
  std::sort(a.begin(), a.end());
  treap::Node *root = NULL;
  std::vector<treap::Node> nodes(n);
  for (int i = 0; i < n; ++i) {
    nodes[i] = treap::Node(a[i]);
    root = treap::merge(root, &nodes[i]);
  }
  for (int i = 0; i < m; ++i) {
    b[i] = io.nextUInt();
  }
  std::sort(b.begin(), b.end());
  while (!b.empty()) {
    treap::Node *u, *v, *x, *y;
    int s = b.back();
    b.pop_back();
    if (n < s) {
      puts("NIE");
      return 0;
    }
    std::tie(u, x) = treap::split_by_size(root, n - s);
    int w = x->val;
    for (auto p = x; p; p = p->l) {
      w = p->val;
      p->push();
    }
    if (w <= 0) {
      puts("NIE");
      return 0;
    }
    std::tie(x, y) = treap::split_by_value(x, w + 1);
    std::tie(u, v) = treap::split_by_value(u, w);
    if (y) y->apply(-1);
    if (x) x->apply(-1);
    root = treap::merge(treap::merge(u, x), treap::merge(v, y));
  }
  puts("TAK");
  return 0;
}

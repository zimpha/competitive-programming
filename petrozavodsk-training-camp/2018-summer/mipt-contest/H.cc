#include <cstdio>
#include <cassert>
#include <functional>
#include <algorithm>

const int N = 2e5 + 10;

using pii = std::pair<int, int>;

struct Node {
  Node *l, *r;
  std::pair<int, int> iv;
  int size, sum;
  Node() = default;
  void init(int vl, int vr) {
    l = r = NULL;
    iv = {vl, vr};
    size = 1;
    sum = iv.second - iv.first;
  }
  Node* update() {
    size = 1;
    sum = iv.second - iv.first;
    if (l) size += l->size, sum += l->sum;
    if (r) size += r->size, sum += r->sum;
    return this;
  }
} pool[N];

int perm[N], next[N];

int get_size(Node *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

std::pair<Node*, Node*> split_by_value(Node *o, int v) {//[-inf, v), [v, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  if (perm[o->iv.first] < v) {
    std::tie(o->r, r) = split_by_value(o->r, v);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_value(o->l, v);
    r = o;
  }
  o->update();
  return {l, r};
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

int rank(Node *o, int sum) {
  if (!o) return 0;
  int ls = o->l ? o->l->sum : 0;
  if (sum <= ls) return rank(o->l, sum);
  ls += o->iv.second - o->iv.first;
  if (sum <= ls) return get_size(o->l);
  return get_size(o->l) + 1 + rank(o->r, sum - ls);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &perm[i]);
  }
  next[n] = n;
  for (int i = n - 1; i >= 0; --i) {
    int j = i + 1;
    while (j < n && perm[j] < perm[i]) j = next[j];
    next[i] = j;
  }
  Node *root = NULL;
  for (int l = 0; l < n; l = next[l]) {
    pool[l].init(l, next[l]);
    root = merge(root, pool + l);
  }
  for (int i = 0; i < m; ++i) {
    int op, x;
    scanf("%d%d", &op, &x);
    Node *a, *o, *b;
    if (op == 2) ++x;
    int rk = rank(root, x);
    std::tie(a, b) = split_by_size(root, rk);
    assert(b);
    std::tie(o, b) = split_by_size(b, 1);
    if (a) x -= a->sum;
    if (op == 1) {
      printf("%d\n", perm[o->iv.first + x - 1]);
      root = merge(a, merge(o, b));
    } else {
      if (x == 1) root = merge(a, merge(o, b));
      else {
        int l = o->iv.first + x - 1, r = o->iv.second;
        o->init(o->iv.first, l);
        root = merge(a, merge(o, b));
        for (; l < r; l = next[l]) {
          pool[l].init(l, std::min(r, next[l]));
          std::tie(a, b) = split_by_value(root, perm[l]);
          root = merge(a, merge(pool + l, b));
        }
      }
    }
  }
  return 0;
}

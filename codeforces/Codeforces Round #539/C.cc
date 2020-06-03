#include <cstdio>
#include <limits>
#include <iostream>
#include <functional>

using int64 = long long;

struct Node {
  Node *l, *r;
  int64 t, lt, rt;
  int64 s, ls, rs;
  int64 ret, mx;
  int size;
  Node(int _s, int _t): l(0), r(0), t(_t), s(_s) {
    update();
  }
  Node* update() {
    size = 1;
    lt = rt = t;
    ls = rs = s;
    ret = 0;
    mx = std::numeric_limits<int64>::max();
    if (l) {
      size += l->size;
      lt = l->lt;
      ls = l->ls;
      mx = std::min(mx, l->mx);
      ret += l->ret + l->rs * (t - l->rt);
    }
    mx = std::min(mx, ret);
    if (r) {
      size += r->size;
      rt = r->rt;
      rs = r->rs;
      ret += s * (r->lt - t);
      mx = std::min(mx, ret + r->mx);
      ret += r->ret;
    }
    mx = std::min(mx, ret);
    return this;
  }
};

int get_size(Node *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

std::pair<Node*, Node*> split_by_time(Node *o, int t) {//[-inf, t), [t, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  if (o->t < t) {
    std::tie(o->r, r) = split_by_time(o->r, t);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_time(o->l, t);
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

Node* kth(Node *o, int k) {
  int cnt = get_size(o->l);
  if (cnt + 1 == k) return o;
  if (k <= cnt) return kth(o->l, k);
  else return kth(o->r, k - cnt - 1);
}

double simulate(Node* o, int64 r, int64 v) {
  if (!o) return -1;
  //printf("=%lld %lld\n", o->t, o->s);
  if (o->mx + v > 0 && v + o->ret + o->rs * (r - o->rt) > 0) return -1;
  if (!o->l && !o->r) return o->t - (double)v / o->s;
  double res = -1;
  if (o->l) res = simulate(o->l, o->t, v);
  if (res != -1) return res;
  if (o->l) v += o->l->ret + o->l->rs * (o->t - o->l->rt);
  int rr = o->r ? o->r->lt : r;
  if (v >= 0 && v + o->s * (rr - o->t) <= 0) return o->t - (double)v / o->s;
  v += o->s * (rr - o->t);
  return simulate(o->r, r, v);
}

void trans(Node* o) {
  if (!o) return;
  trans(o->l);
  printf("%lld %lld\n", o->t, o->s);
  trans(o->r);
}

int main() {
  Node* rt = new Node(0, 0);
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int op, t, s, l, r, v;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &t, &s);
      Node* p = new Node(s, t);
      Node *a, *b;
      std::tie(a, b) = split_by_time(rt, t);
      rt = merge(a, merge(p, b));
    } else if (op == 2) {
      scanf("%d", &t);
      Node *a, *b, *c;
      std::tie(a, b) = split_by_time(rt, t);
      std::tie(b, c) = split_by_time(b, t + 1);
      rt = merge(a, c);
    } else {
      scanf("%d%d%d", &l, &r, &v);
      Node *a, *b, *c;
      std::tie(a, b) = split_by_time(rt, l);
      std::tie(b, c) = split_by_time(b, r + 1);
//      printf("xxx %d %d %d\n", l, r, v);
//      trans(b);
      // do calc here
      if (v == 0) printf("%d\n", l);
      else printf("%.10f\n", simulate(b, r, v));
      rt = merge(a, merge(b, c));
    }
  }
  return 0;
}

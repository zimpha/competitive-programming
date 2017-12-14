#include <cmath>
#include <cstdio>
#include <iostream>
#include <functional>

using int64 = unsigned long long;
using int128 = __int128;

struct node_t {
  node_t *l, *r;
  int size;
  int64 value;
  node_t(int64 v): l(0), r(0), size(1), value(v) {}
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

std::pair<node_t*, node_t*> split_by_value(node_t *o, int64 v) {//[-inf, v), [v, +inf)
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

node_t* kth(node_t *o, int k) {
  int cnt = get_size(o->l);
  if (cnt + 1 == k) return o;
  if (k <= cnt) return kth(o->l, k);
  else return kth(o->r, k - cnt - 1);
}

void sum(int n) {
  auto pow = [](int base, int exp) {
    int64 r = 1;
    for (int i = 0; i < exp; ++i) r *= base;
    return r;
  };
  node_t *root = 0;
  int128 ret = 0;
  for (int i = 1; i <= n; ++i) {
    int a = __builtin_popcount(i * 3);
    int b = __builtin_popcount(i * 2);
    int c = __builtin_popcount(i + 1);
    int64 u = pow(2, a) + pow(3, b) + c;
    node_t *x, *y;
    std::tie(x, y) = split_by_value(root, u);
    root = merge(x, merge(new node_t(u), y));
    if (i >= 4) {
      int64 sum = 0;
      double mx = 0;
      for (int j = i, it = 0; j >= 4 && it < 10; --j, ++it) {
        int64 a = kth(root, j)->value;
        int64 b = kth(root, j - 1)->value;
        int64 c = kth(root, j - 2)->value;
        int64 d = kth(root, j - 3)->value;
        if (b + c + d > a) {
          double s = (b + c + d + a) / 2.;
          double area = sqrt((s - a) * (s - b) * (s - c) * (s - d));
          if (area > mx) {
            sum = a + b + c + d;
            mx = area;
          }
        }
      }
      //printf("%d: %d\n", i, sum);
      ret += sum;
    }
  }
  const int64 base = 1000000000000000000ll;
  if (ret < base) printf("%lld\n", (int64)ret);
  else printf("%lld%018lld\n", int64(ret / base), int64(ret % base));
}

int main() {
  sum(150);
  sum(3000000);
  return 0;
}

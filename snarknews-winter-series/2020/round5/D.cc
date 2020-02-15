#include <cstdio>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;
const int inf = 2e9;

struct Node {
  int64 sum;
  int mi, smi, cmi;
  int t_add;
  void apply_max(int v) {
    sum += (int64)(v - mi) * cmi;
    mi = v;
  }
  void apply(int l, int r, int v) {
    sum += int64(r - l) * v;
    mi += v, smi += v;
    t_add += v;
  }
} T[N << 2];

int a[N];

void update(Node &o, const Node &l, const Node &r) {
  o.sum = l.sum + r.sum;
  o.mi = std::min(l.mi, r.mi);
  o.smi = std::min(l.smi, r.smi);
  o.cmi = 0;
  if (o.mi == l.mi) o.cmi += l.cmi;
  else o.smi = std::min(o.smi, l.mi);
  if (o.mi == r.mi) o.cmi += r.cmi;
  else o.smi = std::min(o.smi, r.mi);
}

void push(int o, int l, int r) {
  if (T[o].t_add) {
    int m = (l + r) >> 1;
    T[o << 1].apply(l, m, T[o].t_add);
    T[o << 1 | 1].apply(m, r, T[o].t_add);
    T[o].t_add = 0;
  }
  if (T[o << 1].mi < T[o].mi && T[o << 1].smi > T[o].mi) T[o << 1].apply_max(T[o].mi); 
  if (T[o << 1 | 1].mi < T[o].mi && T[o << 1 | 1].smi > T[o].mi) T[o << 1 | 1].apply_max(T[o].mi); 
}

void build(int o, int l, int r) {
  T[o].t_add = 0;
  if (l + 1 == r) {
    int x;
    scanf("%d", &x);
    a[l] = x;
    T[o].sum = x;
    T[o].mi = x;
    T[o].smi = inf;
    T[o].cmi = 1;
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  update(T[o], T[o << 1], T[o << 1 | 1]);
}

void add(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].apply(l, r, v);
    return;
  }
  int m = (l + r) >> 1;
  push(o, l, r);
  if(L < m) add(o << 1, l, m, L, R, v);
  if(m < R) add(o << 1 | 1, m, r, L, R, v);
  update(T[o], T[o << 1], T[o << 1 | 1]);
}

void max(int o, int l, int r, int L, int R, int v) {
  int m = (l + r) >> 1;
  if (L <= l && R >= r) {
    if (T[o].mi >= v) return;
    else if (T[o].smi > v) {
      T[o].apply_max(v);
      return;
    }
    push(o, l, r);
    max(o << 1, l, m, L, R, v);
    max(o << 1 | 1, m, r, L, R, v);
    update(T[o], T[o << 1], T[o << 1 | 1]);
    return;
  }
  push(o, l, r);
  if (L < m) max(o << 1, l, m, L, R, v);
  if (R > m) max(o << 1 | 1, m, r, L, R, v);
  update(T[o], T[o << 1], T[o << 1 | 1]);
}

int64 sum(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].sum;
  push(o, l, r);
  int m = (l + r) >> 1;
  int64 ret = 0;
  if (L < m) ret += sum(o << 1, l, m, L, R);
  if (R > m) ret += sum(o << 1 | 1, m, r, L, R);
  return ret;
}

int main() {
  int n, q;
  scanf("%d", &n);
  build(1, 0, n);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int op, l, r, d;
    scanf("%d%d%d%d", &op, &l, &r, &d);
    --l;
    if (op == 1) {
      add(1, 0, n, l, r, d);
    } else {
      int64 ret = sum(1, 0, n, l, r);
      add(1, 0, n, l, r, -d);
      max(1, 0, n, l, r, 0);
      ret -= sum(1, 0, n, l, r);
      printf("%lld\n", ret);
    }
  }
  return 0;
}

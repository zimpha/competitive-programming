#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;

const int N = 5e5 + 10, inf = 2e9;

std::vector<pii> update[N];
std::vector<int> query[N];
int ret[N];

namespace seg {
struct SubNode {
  pii mx, sub, sub_tag;
  int mi;
  void init() {
    mx = {-inf, -inf};
    sub = {inf, inf};
    sub_tag = {0, 0};
    mi = inf;
  }
  void apply(int v) { mx.second = v; }
  void apply_sub(int first, int second) {
    if (first && mx.first != -inf) sub.first = sub_tag.first = first;
    if (second) sub.second = sub_tag.second = second;
    mi = std::min(sub.first, sub.second);
  }
};

struct Node {
  pii mx;
  SubNode sub[2];
  bool valid;
  void init() {
    mx = {-inf, -inf};
    sub[0].init();
    sub[1].init();
    valid = false;
  }
  void apply(int v) { mx.second = v; }
} T[N << 2];

void merge_pii(pii &o, const pii &l, const pii &r) {
  o.second = std::max(l.second, r.second);
  o.first = std::max(
    l.second == o.second ? l.first : l.second,
    r.second == o.second ? r.first : r.second);
}

void merge_sub(SubNode &o, SubNode l, const SubNode &r) {
  merge_pii(o.mx, l.mx, r.mx);
  o.sub.second = std::min(
    o.mx.second == l.mx.second ? l.sub.second : inf,
    o.mx.second == r.mx.second ? r.sub.second : inf);
  o.sub.first = std::min(
    o.mx.second == l.mx.second ? l.sub.first : l.mi,
    o.mx.second == r.mx.second ? r.sub.first : r.mi);
  o.mi = std::min(o.sub.first, o.sub.second);
}

void pull(Node &o, const Node &l, const Node &r) {
  merge_pii(o.mx, l.mx, r.mx);
  merge_sub(o.sub[0], l.sub[0], r.sub[0]);
  if (l.mx.second == r.mx.second) {
    merge_sub(o.sub[1], l.sub[1], r.sub[1]);
  } else if (l.mx.second == o.mx.second) {
    o.sub[1] = l.sub[1];
    merge_sub(o.sub[0], o.sub[0], r.sub[1]);
  } else {
    o.sub[1] = r.sub[1];
    merge_sub(o.sub[0], o.sub[0], l.sub[1]);
  }
  o.valid = l.valid || r.valid;
}

void push_sub(SubNode &x, const SubNode &y) {
  if (y.mx.second <= x.mx.second) {
    x.apply(y.mx.second);
    x.apply_sub(y.sub_tag.first, y.sub_tag.second);
  } else {
    x.apply_sub(y.sub_tag.first, y.sub_tag.first);
  }
}

void push(int o) {
  for (int u = o * 2; u <= o * 2 + 1; ++u) if (T[u].valid) {
    if (T[o].mx.second <= T[u].mx.second) {
      T[u].apply(T[o].mx.second);
      push_sub(T[u].sub[1], T[o].sub[1]);
    } else {
      push_sub(T[u].sub[1], T[o].sub[0]);
    }
    if (T[u].mx.first != -inf) {
      push_sub(T[u].sub[0], T[o].sub[0]);
    }
  }
  T[o].sub[0].sub_tag = {0, 0};
  T[o].sub[1].sub_tag = {0, 0};
}

void build(int o, int l, int r) {
  T[o].init();
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
}

template<int part>
void modify(int o, int l, int r, int v) {
  if (!T[o].valid || (!part && T[o].mx.first == -inf)) return;
  if (T[o].sub[part].mx.second < v) {
    T[o].sub[part].apply_sub(v, v);
    return;
  } else if (T[o].sub[part].mx.first < v) {
    T[o].sub[part].apply(v);
    T[o].sub[part].apply_sub(v, 0);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (T[o].mx.second == T[o << 1].mx.second) {
    modify<part>(o << 1, l, m, v);
  } else if (!part) {
    modify<0>(o << 1, l, m, v);
    modify<1>(o << 1, l, m, v);
  }
  if (T[o].mx.second == T[o << 1 | 1].mx.second) {
    modify<part>(o << 1 | 1, m, r, v);
  } else if (!part) {
    modify<0>(o << 1 | 1, m, r, v);
    modify<1>(o << 1 | 1, m, r, v);
  }
  pull(T[o], T[o << 1], T[o << 1 | 1]);
}

void append(int o, int l, int r, int L, int R, int v) {
  if (!T[o].valid) return;
  if (L <= l && R >= r) {
    if (T[o].mx.second < v) {
      modify<0>(o, l, r, v);
      modify<1>(o, l, r, v);
      return;
    } else if (T[o].mx.first < v) {
      T[o].apply(v);
      modify<0>(o, l, r, v);
      return;
    }
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) append(o << 1, l, m, L, R, v);
  if (R > m) append(o << 1 | 1, m, r, L, R, v);
  pull(T[o], T[o << 1], T[o << 1 | 1]);
}

void add(int o, int l, int r, int x) {
  if (l + 1 == r) {
    T[o].init();
    T[o].mx.second = inf;
    T[o].sub[1].mx.second = inf;
    T[o].valid = true;
    return;
  }
  int m = (l + r) >> 1;
  push(o);
  if (x < m) add(o << 1, l, m, x);
  else add(o << 1 | 1, m, r, x);
  pull(T[o], T[o << 1], T[o << 1 | 1]);
}

void get_ret(int o, int l, int r, int L, int R, int w, int idx) {
  if (!T[o].valid || std::min(T[o].sub[0].mi, T[o].sub[1].mi) >= w) return;
  if (l + 1 == r) {
    T[o].init();
    ret[l] = idx;
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) get_ret(o << 1, l, m, L, R, w, idx);
  if (R > m) get_ret(o << 1 | 1, m, r, L, R, w, idx);
  pull(T[o], T[o << 1], T[o << 1 | 1]);
}

}

int main() {
  int n, q, m = 0;
  scanf("%d%d", &n, &q);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    update[i].emplace_back(m, x);
  }
  for (int i = 0, x, y, op; i < q; ++i) {
    scanf("%d%d", &op, &x);
    if (op == 1) {
      scanf("%d", &y);
      update[x - 1].emplace_back(m, y);
    } else {
      query[x - 1].push_back(m++);
    }
  }
  if (!m) return 0;
  seg::build(1, 0, m);
  for (int i = 0; i < m; ++i) ret[i] = -1;
  for (int i = 0; i < n; ++i) {
    for (auto &x: query[i]) seg::add(1, 0, m, x);
    update[i].emplace_back(m, 0);
    for (size_t j = 0; j + 1 < update[i].size(); ++j) {
      if (update[i][j].first != update[i][j + 1].first) {
        seg::get_ret(1, 0, m, update[i][j].first, update[i][j + 1].first, update[i][j].second, i + 1);
        seg::append(1, 0, m, update[i][j].first, update[i][j + 1].first, update[i][j].second);
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    printf("%d\n", ret[i]);
  }
  return 0;
}

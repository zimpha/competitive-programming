#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using i64 = long long;

const int N = 1e5 + 10;
const int inf = 1e9;

struct Node {
  i64 value, cnt;
  i64 tag_delta;
  int tag_cnt;
  bool active;
  void apply_delta(i64 v) {
    tag_delta += v;
    value += v;
  }
  void apply_cnt(int v) {
    tag_cnt += v;
    cnt += v;
  }
} T[N << 2];

int ddl[N], t[N];
int n, m;

void push(int o) {
  if (T[o].tag_cnt) {
    if (T[o << 1].active) T[o << 1].apply_cnt(T[o].tag_cnt);
    if (T[o << 1 | 1].active) T[o << 1 | 1].apply_cnt(T[o].tag_cnt);
    T[o].tag_cnt = 0;
  }
  if (T[o].tag_delta) {
    if (T[o << 1].active) T[o << 1].apply_delta(T[o].tag_delta);
    if (T[o << 1 | 1].active) T[o << 1 | 1].apply_delta(T[o].tag_delta);
    T[o].tag_delta = 0;
  }
}

void pull(int o) {
  T[o].active = T[o << 1].active || T[o << 1 | 1].active;
  if (!T[o].active) return;
  if (T[o << 1].active) T[o].cnt = T[o << 1].cnt;
  else T[o].cnt = T[o << 1 | 1].cnt;
  if (T[o << 1 | 1].active) {
    T[o].cnt = std::max(T[o].cnt, T[o << 1 | 1].cnt);
  }
}

i64 get_value(int o, int l, int r, int x) {
  assert(T[o].active);
  if (l + 1 == r) {
    return T[o].value + (i64)T[o].tag_cnt * ddl[l];
  }
  push(o);
  int m = (l + r) >> 1;
  if (x < m) return get_value(o << 1, l, m, x);
  else return get_value(o << 1 | 1, m, r, x);
}

// first one <= x
std::pair<i64, int> lower(int o, int l, int r, int x) {
  if (!T[o].active) return {-1, -1};
  if (l + 1 == r) return {
    T[o].value + (i64)T[o].tag_cnt * ddl[l], l
  };
  push(o);
  int m = (l + r) >> 1;
  std::pair<i64, int> ret = {-1, -1};
  if (T[o << 1 | 1].active && m <= x) ret = lower(o << 1 | 1, m, r, x);
  if (ret.second == -1) ret = lower(o << 1, l, m, x);
  return ret;
}

// first one >= x
std::pair<i64, int> upper(int o, int l, int r, int x) {
  if (!T[o].active) return {-1, -1};
  if (l + 1 == r) return {
    T[o].value + (i64)T[o].tag_cnt * ddl[l], l
  };
  push(o);
  int m = (l + r) >> 1;
  std::pair<i64, int> ret = {-1, -1};
  if (T[o << 1].active && x < m) ret = upper(o << 1, l, m, x);
  if (ret.second == -1) ret = upper(o << 1 | 1, m, r, x);
  return ret;
}

void set_cnt(int o, int l, int r, int x, i64 cnt) {
  assert(T[o].active);
  if (l + 1 == r) {
    T[o].cnt = cnt;
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (x < m) set_cnt(o << 1, l, m, x, cnt);
  else set_cnt(o << 1 | 1, m, r, x, cnt);
  pull(o);
}

void add_delta(int o, int l, int r, int L, int R, int delta) {
  if (!T[o].active) return;
  if (L <= l && R >= r) {
    T[o].apply_delta(delta);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add_delta(o << 1, l, m, L, R, delta);
  if (R > m) add_delta(o << 1 | 1, m, r, L, R, delta);
  pull(o);
}

void add_cnt(int o, int l, int r, int L, int R) {
  if (!T[o].active) return;
  if (L <= l && R >= r) {
    T[o].apply_cnt(1);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add_cnt(o << 1, l, m, L, R);
  if (R > m) add_cnt(o << 1 | 1, m, r, L, R);
  pull(o);
}

int get_max(int o, int l, int r) {
  assert(T[o].active);
  if (l + 1 == r) return l;
  push(o);
  int m = (l + r) >> 1;
  if (T[o << 1].active && T[o << 1].cnt >= 0) return get_max(o << 1, l, m);
  else return get_max(o << 1 | 1, m, r);
}

void deactive(int o, int l, int r, int x) {
  if (l + 1 == r) {
    T[o].active = false;
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (x < m) deactive(o << 1, l, m, x);
  else deactive(o << 1 | 1, m, r, x);
  pull(o);
}

void active(int o, int l, int r, int x, i64 w) {
  if (l + 1 == r) {
    T[o].cnt = 0;
    T[o].tag_cnt = 0;
    T[o].tag_delta = 0;
    T[o].value = w;
    T[o].active = true;
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (x < m) active(o << 1, l, m, x, w);
  else active(o << 1 | 1, m, r, x, w);
  pull(o);
}

void update_cnt(int p) {
  i64 vp = get_value(1, 0, m, p);
  auto nx = upper(1, 0, m, p + 1);
  if (nx.second == -1) {
    set_cnt(1, 0, m, p, -inf);
  } else {
    int step = ddl[nx.second] - ddl[p];
    i64 cnt = (vp - nx.first + step - 1) / step;
    set_cnt(1, 0, m, p, -cnt);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &t[i]);
  for (int i = 0; i <= n; ++i) ddl[i] = t[i];
  std::sort(ddl, ddl + n + 1);
  m = std::unique(ddl, ddl + n + 1) - ddl;
  active(1, 0, m, 0, t[1]);
  int mx = t[1];
  for (int i = 2; i <= n; ++i) {
    mx = std::max(mx, t[i]);
    int p = std::lower_bound(ddl, ddl + m, t[i]) - ddl;
    auto left = lower(1, 0, m, p - 1);
    auto cur = lower(1, 0, m, p);
    auto right = upper(1, 0, m, p + 1);

    i64 dp_p = left.first + t[i];
    add_delta(1, 0, m, 0, p, mx);
    if (cur.second == p) {
      active(1, 0, m, p, std::min(dp_p, cur.first + t[i]));
    } else if (mx != t[i]) {
      active(1, 0, m, p, dp_p);
    }
    if (right.second != -1 && p + 1 < m) {
      add_cnt(1, 0, m, p + 1, m);
    }
    update_cnt(left.second);
    if (cur.second == p || mx != t[i]) {
      update_cnt(p);
    }
    while (T[1].active && T[1].cnt >= 0) {
      int x = get_max(1, 0, m);
      int y = upper(1, 0, m, x + 1).second;
      deactive(1, 0, m, y);
      update_cnt(x);
    }
  }
  i64 ret = lower(1, 0, m, m - 1).first;
  for (int i = 1; i <= n; ++i) ret -= t[i];
  printf("%lld\n", ret);
  return 0;
}
